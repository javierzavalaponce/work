// Test para analizador lógico
// Pin 8 y Pin 9 parpadeando a diferentes frecuencias

const uint8_t pin1 = 8;
const uint8_t pin2 = 9;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

const unsigned long interval1 = 500;  // 500 ms
const unsigned long interval2 = 200;  // 200 ms

bool state1 = LOW;
bool state2 = LOW;

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Control pin 8
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
    state1 = !state1;
    digitalWrite(pin1, state1);
  }

  // Control pin 9
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    state2 = !state2;
    digitalWrite(pin2, state2);
  }
}


