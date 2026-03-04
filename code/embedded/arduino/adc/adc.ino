void setup() {
  Serial.begin(9600);
}

unsigned long previousMillis = 0;
const unsigned long interval = 360;

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    int adc2 = analogRead(A2);
    int adc4 = analogRead(A4);
    int adc5 = analogRead(A5);
    
    Serial.print(adc2);
    Serial.print(",\t");
    Serial.print(adc4);
    Serial.print(",\t");
    Serial.println(adc5);
  }
}
