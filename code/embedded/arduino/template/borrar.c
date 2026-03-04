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

void task1() {
  DDRB |= (1 << PB0);
  while (1) {
    PORTB ^= (1 << PB0);
    for (volatile long i=0;i<50000;i++);
  }
}

void task2() {
  DDRB |= (1 << PB1);
  while (1) {
    PORTB ^= (1 << PB1);
    for (volatile long i=0;i<50000;i++);
  }
}

void task3() {
  while (1) {
    // tarea dummy
  }
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

ISR(TIMER1_COMPA_vect, ISR_NAKED) {
  static uint8_t signal = 0;
  signal = (signal)?0:1;
  if(signal) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);

  saveContext();

  asm volatile(
    "in r24, __SP_L__\n\t"
    "in r25, __SP_H__\n\t"
  );

  tasks[currentTask].sp = (uint8_t*)((uint16_t)SP);

  currentTask++;
  if (currentTask >= TASK_COUNT)
    currentTask = 0;

  SP = (uint16_t)tasks[currentTask].sp;

  restoreContext();

  asm volatile("reti");
}

void setupTimer() {
  cli(); // disable interrupts

  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 3124;              // 200ms
  TCCR1B |= (1 << WGM12);    // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024
  TIMSK1 |= (1 << OCIE1A);   // enable compare interrupt
  sei(); // enable interrupts
}

void setup() {

  DDRB |= (1 << PB0) | (1 << PB1);
  pinMode(LED_BUILTIN, OUTPUT);
  initTask(0, task1);
  initTask(1, task2);
  initTask(2, task3);

  SP = (uint16_t)tasks[0].sp;

  setupTimer();
}

void loop() {}

