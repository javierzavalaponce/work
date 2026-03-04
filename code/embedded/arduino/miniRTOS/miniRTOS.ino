#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define TASK_COUNT 3
#define STACK_SIZE 128

typedef struct {
  uint8_t *sp;
  uint8_t stack[STACK_SIZE];
} task_t;

task_t tasks[TASK_COUNT];
volatile uint8_t currentTask = 0;
volatile uint8_t signal = 0;


void task1() {
  static uint8_t t1 = 0;
  t1 = (t1)?0:1;
  if(t1) digitalWrite(8, HIGH);
  else digitalWrite(8, LOW);
}

void task2() {
  static uint8_t t2 = 0;
  t2 = (t2)?0:1;
  if(t2) digitalWrite(9, HIGH);
  else digitalWrite(9, LOW);
}

void task3() {
  // Tarea dummy (puedes expandir luego)
}

void (*taskTable[TASK_COUNT])() = {task1, task2, task3};

void setupTimer1() {
  cli(); // disable interrupts

  TCCR1A = 0;
  TCCR1B = 0;

  OCR1A = 3124;              // 200ms
  TCCR1B |= (1 << WGM12);    // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024

  TIMSK1 |= (1 << OCIE1A);   // enable compare interrupt

  sei(); // enable interrupts
}

void initTask(uint8_t id, void (*func)()) {
  uint8_t *stackTop = tasks[id].stack + STACK_SIZE - 1;

  // Dirección de retorno simulada
  stackTop--;
  *stackTop = (uint16_t)func & 0xFF;
  stackTop--;
  *stackTop = ((uint16_t)func >> 8) & 0xFF;

  tasks[id].sp = stackTop;
}

void saveContext() {
  asm volatile(
    "push r0\n\t"
    "in r0, __SREG__\n\t"
    "cli\n\t"
    "push r0\n\t"
    "push r1\n\t"
    "clr r1\n\t"
    "push r2\n\t push r3\n\t push r4\n\t push r5\n\t"
    "push r6\n\t push r7\n\t push r8\n\t push r9\n\t"
    "push r10\n\t push r11\n\t push r12\n\t push r13\n\t"
    "push r14\n\t push r15\n\t push r16\n\t push r17\n\t"
    "push r18\n\t push r19\n\t push r20\n\t push r21\n\t"
    "push r22\n\t push r23\n\t push r24\n\t push r25\n\t"
    "push r26\n\t push r27\n\t push r28\n\t push r29\n\t"
    "push r30\n\t push r31\n\t"
  );
}

void restoreContext() {
  asm volatile(
    "pop r31\n\t pop r30\n\t pop r29\n\t pop r28\n\t"
    "pop r27\n\t pop r26\n\t pop r25\n\t pop r24\n\t"
    "pop r23\n\t pop r22\n\t pop r21\n\t pop r20\n\t"
    "pop r19\n\t pop r18\n\t pop r17\n\t pop r16\n\t"
    "pop r15\n\t pop r14\n\t pop r13\n\t pop r12\n\t"
    "pop r11\n\t pop r10\n\t pop r9\n\t pop r8\n\t"
    "pop r7\n\t pop r6\n\t pop r5\n\t pop r4\n\t"
    "pop r3\n\t pop r2\n\t pop r1\n\t pop r0\n\t"
    "out __SREG__, r0\n\t"
    "pop r0\n\t"
  );
}


ISR(TIMER1_COMPA_vect) {
  signal = (signal)?0:1;
  if(signal) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);

  /*
  saveContext();

  asm volatile(
    "in r24, __SP_L__\n\t"
    "in r25, __SP_H__\n\t"
  );

  tasks[currentTask].sp = (uint8_t*)((uint16_t)SP);
  */
  currentTask++;
  if (currentTask >= TASK_COUNT)
    currentTask = 0;
/*
    SP = (uint16_t)tasks[currentTask].sp;
  
  restoreContext();

  asm volatile("reti");
  */
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  setupTimer1();
}

void loop() {
  taskTable[currentTask]();
}
