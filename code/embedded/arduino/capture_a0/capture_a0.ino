#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <LiquidCrystal.h>

const int RS = 8;
const int EN = 9;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;

const int pin_BL = 10; // arduino pin wired to LCD backlight circuit

LiquidCrystal lcd( RS,  EN,  d4,  d5,  d6,  d7);


const int pinADC = A0;
volatile int x = 0;
volatile int sampleToSend = 0;
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
  // Filtro RC
  static float y = 0.0;
  const float alpha = 0.2;

  // Alternar pin para medir con analizador lógico
  signal = !signal;
  digitalWrite(LED_BUILTIN, signal ? HIGH : LOW);

  // Leer ADC y aplicar filtro RC: y[n] = alpha * x[n] + (1 - alpha) * y[n-1]
  digitalWrite(12,HIGH);
  // Leer ADC
  x = analogRead(pinADC);
  //centrar en 0 (Vbias de 2.5V)
  x = x - 512;
  // Aplicar filtro RC
  y = y + alpha * (x - y);
  sampleToSend = (int)(y + 512); // Recentrar para enviar valor entre 0-1023
  readyToSend = true; // Señalamos que hay dato listo
  digitalWrite(12,LOW);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(12, LOW);

    lcd.begin(16, 2);  // Columnas, filas
  lcd.setCursor(0, 0);  // Columna, fila (0-indexed)
  lcd.print("EmulV0 115.2K8n1");  // Mensaje línea 1
  lcd.setCursor(0, 1);
  lcd.print("S:1ms- aud/ser");

  Serial.begin(115200); 
  setupTimer1();
}

void loop()
{
  // Enviar dato por Serial si hay uno nuevo
  if (readyToSend)
  {
    readyToSend = false;
    Serial.println(sampleToSend-512); // Enviar valor centrado en 0
  }
}