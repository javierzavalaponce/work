#include <Arduino.h>
#include <Wire.h>
#define AS5600_ADDR 0x36

  // Pines BTS7960
const int RPWM = 5;
const int LPWM = 6;
const int R_EN = 7;
const int L_EN = 8;

#define MD (1<<3) //MAGNET DETECTED
#define ML (1<<4) //MAGNET Low
#define MH (1<<5) //MAGNET  high

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

/*
Que me puede decir el encoder
STATUS (0x0B)
MD	Magnet Detected	 - Hay imán válido
ML	Magnet Low	- Campo muy débil
MH	Magnet High	- Campo demasiado fuerte

--------
RAW ANGLE 0x0C y 0x0D [0-4095 12bit adc]
θ=RAW⋅360​ /4096
---


ANGLE (filtrado)
0x0E y 0x0F Es parecido a RAW pero:
suavizado,
compensado,
filtrado.
RAW suele ser mejor para control y debugging.

---
Intensidad magnética - validar alineación.
AGC 0x1A Automatic Gain Control.
Te dice cuánto esfuerzo hace el chip para “ver” el imán.
Interpretación intuitiva:
AGC	Significado
bajo	imán fuerte/cerca
alto	imán lejos/débil

---
MAGNITUDE 0x1B y 0x1C

Magnitud real del campo magnético.
Sirve para:
centrar el imán,
detectar wobble,
detectar excentricidad.




uint16_t readAngleFiltered(void);
uint8_t read_AGC(void);
uint16_t readMagnitud(void);


*/


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
  Serial.println("uart enabled -** as5600..");
  analogWrite(RPWM, 30);
}

void loop() {
  uint16_t raw = readAngleRaw();
  uint8_t status = readStatus();
uint8_t md,ml,mh;

#define MD (1<<3) //MAGNET DETECTED

  md = status & MD;
  ml = status & ML;
  mh = status & MH;

  //float angle = raw * 360.0 / 4096.0;
  Serial.print("STATUS: ");
  Serial.print(status, BIN);

  Serial.print("  RAW: ");
  Serial.println(raw);

  //Serial.print("  ANGLE: ");
  //Serial.println(angle);

  delay(80);
}
