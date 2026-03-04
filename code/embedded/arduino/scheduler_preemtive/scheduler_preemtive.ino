#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define TASK_COUNT 3

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

ISR(TIMER1_COMPA_vect) {
  signal = (signal)?0:1;
  if(signal) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);
  currentTask++;
  if (currentTask >= TASK_COUNT)
    currentTask = 0;
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

