#include <avr/interrupt.h>

#define TASKS 3
volatile uint8_t currentTask = 0;

void task1() { PORTB ^= (1 << PB0); }
void task2() { PORTB ^= (1 << PB1); }
void task3() { }

void (*taskTable[TASKS])() = {task1, task2, task3};

ISR(TIMER1_COMPA_vect) {
  currentTask++;
  if (currentTask >= TASKS)
    currentTask = 0;
}

void setupTimer() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 3124; // 200ms
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void setup() {
  DDRB |= (1 << PB0) | (1 << PB1);
  setupTimer();
}

void loop() {
  taskTable[currentTask]();
}

