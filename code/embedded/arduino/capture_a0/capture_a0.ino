#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const int pinADC = A0;
volatile int sampleToSend = 0;  // Variable para enviar por Serial
volatile bool readyToSend = false;

void setupTimer1()
{
  cli(); // Deshabilita interrupciones 
  TCCR1A = 0;
  TCCR1B = 0;
  // Configuración para ~1 kHz
  // Con 16 MHz y prescaler 64: OCR1A = 249 → 16e6 / (64 * (249+1)) = 1000 Hz
  OCR1A = 249;
  TCCR1B |= (1 << WGM12);              // Modo CTC
  TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler 64
  TIMSK1 |= (1 << OCIE1A); // Habilitar interrupción por comparación
  sei(); // Habilita interrupciones
}

ISR(TIMER1_COMPA_vect)
{
  static unsigned char signal = 0;
  
  signal = !signal;
  digitalWrite(LED_BUILTIN, signal ? HIGH : LOW);
  // Alternar LEDs
  
  digitalWrite(12,HIGH);
  // Leer ADC
  sampleToSend = analogRead(pinADC);
  readyToSend = true; // Señalamos a loop() que hay dato listo
  digitalWrite(12,LOW);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(12, LOW);

  Serial.begin(115200); 
  setupTimer1();
}

void loop()
{
  // Enviar dato por Serial si hay uno nuevo
  if (readyToSend)
  {
    readyToSend = false;
    Serial.println(sampleToSend - 512);
  }
}