#include <Arduino.h>

// No conectar el puente H BTS7960

// Encoder manual
const int ENC_A = 9;
const int ENC_B = 10;
const int PIN_SW = 11;

// LED indicador
const int ENC_LED = 12;

// Estado anterior del encoder
int lastA;


void setup()
{
    Serial.begin(115200);

    // Encoder
    pinMode(ENC_A, INPUT_PULLUP);
    pinMode(ENC_B, INPUT_PULLUP);

    // Switch
    pinMode(PIN_SW, INPUT_PULLUP);

    // LED
    pinMode(ENC_LED, OUTPUT);

    // Leer estado inicial
    lastA = digitalRead(ENC_A);

    Serial.println("START");
}


void loop()
{
    int A = digitalRead(ENC_A);
    int B = digitalRead(ENC_B);

    // Detectar cambio en A
    if (A != lastA)
    {
        if (A == HIGH)
        {
            if (B == LOW)
            {
                Serial.println("HORARIO");
                digitalWrite(ENC_LED, HIGH);
            }
            else
            {
                Serial.println("ANTIHORARIO");
                digitalWrite(ENC_LED, LOW);
            }
        }

        lastA = A;
    }


    // Switch del encoder
    if (digitalRead(PIN_SW) == LOW)
    {
        Serial.println("SWITCH");

        delay(200);
    }
}