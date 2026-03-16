const int pinADC = A0;

void setup() {
  Serial.begin(115200);
}

void loop() {

  static unsigned long last = 0;

  if (micros() - last >= 125) {   // 8 kHz
    last += 125;

    int sample = analogRead(pinADC);
    Serial.println(sample - 512);
  }
}