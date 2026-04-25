#include <Arduino.h>

  // Pines BTS7960
const int RPWM = 5;
const int LPWM = 6;
const int R_EN = 7;
const int L_EN = 8;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);




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
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("uart enabled..");
}

// the loop function runs over and over again forever
void loop() {

  /*
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
*/



  // Giro sentido 1
  analogWrite(RPWM, 180);  // velocidad (0–255)
  analogWrite(LPWM, 0);
  delay(3000);

  //  Pausa
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  delay(2000);

  //  Giro sentido contrario
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 180);
  delay(3000);

  //  Pausa
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  delay(2000);

  Serial.println("testing 00");

}