  // Arduino + AS5600 - Leer Revoluciones Por Segundo (RPS)
  // Librería: AS5600 de Rob Tillaart

  #include <Arduino.h>
  

// Pines BTS7960
const int RPWM = 5;
const int LPWM = 6;
const int R_EN = 7;
const int L_EN = 8;


void setup_drivermotor() {
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

}




void setup()
{
    Serial.begin(115200);
    setup_drivermotor();
    Serial.println("START");
}

  void loop() {
static unsigned char var = 0;
    
    analogWrite(LPWM, 0);  analogWrite(RPWM, 0);  delay(800); 
    var = ( (var==0) ? 1:0);
    if(var){
    analogWrite(LPWM, 0);  analogWrite(RPWM, 0);  delay(100); 
    analogWrite(RPWM, 60);
    delay(1000); 
    }
    else{ 
    analogWrite(LPWM, 0);  analogWrite(RPWM, 0);  delay(100); 
    analogWrite(LPWM, 60);
    delay(1000); 
    }
  }
    