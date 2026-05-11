// Arduino + AS5600 - Leer Revoluciones Por Segundo (RPS)
// Librería: AS5600 de Rob Tillaart

#include <Wire.h>
#include <AS5600.h>

AS5600 as5600;


  // Pines BTS7960
const int RPWM = 5;
const int LPWM = 6;
const int R_EN = 7;
const int L_EN = 8;


void setup_drivermotor() {
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

  analogWrite(RPWM, 30);
}


// Variables
int lastAngle = 0;
float rpm = 0;
unsigned long lastTime = 0;
int revolutions = 0;
unsigned long sampleCount = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  as5600.begin();

  
  setup_drivermotor();
  
  delay(100);
  Serial.println("AS5600 RPS Reader Started");
  Serial.println("Format: RPS,RPM,Angle");
}

void loop() {
  // Leer ángulo (0-360 grados)
  int rawAngle = as5600.readAngle();
  int currentAngle = map(rawAngle, 0, 4095, 0, 360);
  
  unsigned long currentTime = micros();
  
  if (sampleCount > 0) {
    // Calcular diferencia de ángulo
    int delta = currentAngle - lastAngle;
    
    // Detectar cruce de 0 grados (una vuelta completa)
    if (delta < -180) {
      revolutions++;  // Una vuelta más en sentido horario
      delta += 360;
    } else if (delta > 180) {
      revolutions--;  // Una vuelta en sentido antihorario
      delta -= 360;
    }
    
    // Calcular tiempo transcurrido en segundos
    float deltaTime = (currentTime - lastTime) / 1000000.0;
    
    if (deltaTime > 0) {
      // Calcular RPS (Revoluciones Por Segundo)
      float rps = revolutions / deltaTime;
      
      // Calcular RPM (Revoluciones Por Minuto)
      rpm = rps * 60;
      
      // Enviar datos por Serial
      Serial.print(rps, 2);      // RPS con 2 decimales
      Serial.print(",");
      Serial.print(rpm, 0);      // RPM sin decimales
      Serial.print(",");
      Serial.println(currentAngle);
    }
  }
  
  // Guardar valores para la próxima lectura
  lastAngle = currentAngle;
  lastTime = currentTime;
  sampleCount++;
  
  // Pequeña pausa para no saturar (ajustable)
  delay(10);  // 10ms = 100 lecturas por segundo
}