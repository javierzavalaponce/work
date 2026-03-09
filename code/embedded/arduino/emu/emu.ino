#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define TASK_COUNT 3

volatile uint8_t signal = 0;
float y = 0.0;
float x = 5.0; // Aplica escalon de 5 Volts

float RC = 0.1; //ejemplo de R = 1K  , C = 100u
float Ts = 0.002048;

void setupTimer1() {
  cli(); // disable interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 31;              // 2.048ms
  TCCR1B |= (1 << WGM12);    // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024
  TIMSK1 |= (1 << OCIE1A);   // enable compare interrupt
  sei(); // enable interrupts
}

ISR(TIMER1_COMPA_vect) {
  static float
  signal = (signal)?0:1;
  if(signal) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);
  y = y + (Ts/RC)*(x - y);
  Serial.println(y);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  Serial.begin(115200);
  setupTimer1();
}

void loop() {
  //taskTable[currentTask]();
}

