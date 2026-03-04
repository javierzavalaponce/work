#include <SPI.h>

#define CS 10

void sendDAC(uint16_t value) {

  value &= 0x0FFF;  // limitar a 12 bits

  uint32_t cmd = 0;
  cmd = (0x30UL << 16) | ((uint32_t)value << 4);

  SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE1));

  digitalWrite(CS, LOW);
  SPI.transfer((cmd >> 16) & 0xFF);
  SPI.transfer((cmd >> 8) & 0xFF);
  SPI.transfer(cmd & 0xFF);
  digitalWrite(CS, HIGH);

  SPI.endTransaction();
}

void setup() {
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  SPI.begin();
}

void loop() {
  //static uint16_t dato = 0;

  //sendDAC(4095);

  //dato += 100;
  //if (dato > 4095) dato = 0;

  delay(50);
  sendDAC(4095);
  //delay(50);
}