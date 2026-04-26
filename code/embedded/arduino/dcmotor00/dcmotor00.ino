#include <Arduino.h>
#include <Wire.h>
#define AS5600_ADDR 0x36

// ----------- Lectura RAW ANGLE -----------
uint16_t readAngleRaw() {
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(0x0C); // RAW ANGLE
  if (Wire.endTransmission(false) != 0) {
    return 0;
  }

  delayMicroseconds(10); // estabilidad

  Wire.requestFrom(AS5600_ADDR, 2);

  if (Wire.available() >= 2) {
    uint16_t high = Wire.read();
    uint16_t low = Wire.read();
    return (high << 8) | low;
  }

  return 0;
}

// ----------- Lectura STATUS -----------
uint8_t readStatus() {
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(0x0B); // STATUS
  Wire.endTransmission(false);
  Wire.requestFrom(AS5600_ADDR, 1);

  if (Wire.available()) {
    return Wire.read();
  }
  return 0;
}




  // Pines BTS7960
const int RPWM = 5;
const int LPWM = 6;
const int R_EN = 7;
const int L_EN = 8;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);




   Wire.begin();
  Wire.setClock(100000); // más estable




  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);

  // Habilitar ambos lados
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);

  // Arrancar en stop
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("uart enabled -- as5600..");
  analogWrite(RPWM, 50);
}

void loop() {
  uint16_t raw = readAngleRaw();
  uint8_t status = readStatus();

  //float angle = raw * 360.0 / 4096.0;
  //Serial.print("STATUS: ");
  //Serial.print(status, BIN);

  Serial.print("  RAW: ");
  Serial.println(raw);

  //Serial.print("  ANGLE: ");
  //Serial.println(angle);

  delay(200);
}
