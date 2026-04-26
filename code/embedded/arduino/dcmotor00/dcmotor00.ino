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

// ----------- SETUP -----------
void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(100000); // más estable

  Serial.println("AS5600 test iniciado...");
}

// ----------- LOOP -----------
void loop() {
  uint16_t raw = readAngleRaw();
  uint8_t status = readStatus();

  float angle = raw * 360.0 / 4096.0;

  Serial.print("STATUS: ");
  Serial.print(status, BIN);

  Serial.print("  RAW: ");
  Serial.print(raw);

  Serial.print("  ANGLE: ");
  Serial.println(angle);

  delay(200);
}