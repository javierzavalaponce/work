// Arduino + AS5600 - Leer Revoluciones Por Segundo (RPS)
// Librería: AS5600 de Rob Tillaart

#include <Arduino.h>
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
int lastRawAngle = 0;

float rpm = 0;

unsigned long lastTime = 0;

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

  // ================================
  // 1. Leer posición RAW del encoder
  // ================================
  //
  // El AS5600 entrega:
  //
  // rawAngle ∈ [0,4095]
  //
  // Resolución:
  //
  // 360 / 4096 ≈ 0.0879 grados por paso
  //
  int rawAngle = as5600.readAngle();


  // ================================
  // 2. Tiempo actual
  // ================================
  unsigned long currentTime = micros();


  // ================================
  // 3. Ejecutar sólo después
  //    de tener una muestra previa
  // ================================
  if (sampleCount > 0) {

    // ==========================================
    // 4. Diferencia angular RAW
    // ==========================================
    //
    // Δraw = raw(k) - raw(k-1)
    //
    int deltaRaw = rawAngle - lastRawAngle;


    // ==========================================
    // 5. Corregir wrap-around
    // ==========================================
    //
    // El encoder es circular:
    //
    // 4095 -> 0
    //
    // o:
    //
    // 0 -> 4095
    //
    // Entonces corregimos saltos falsos.
    //
    if (deltaRaw < -2048) {
      deltaRaw += 4096;
    }
    else if (deltaRaw > 2048) {
      deltaRaw -= 4096;
    }


    // ==========================================
    // 6. Tiempo entre muestras
    // ==========================================
    //
    // micros() está en microsegundos
    //
    // convertimos a segundos
    //
    float deltaTime =
      (currentTime - lastTime) / 1000000.0;


    // ==========================================
    // 7. Convertir RAW -> grados
    // ==========================================
    //
    // Δθ = Δraw * (360 / 4096)
    //
    float deltaAngle =
      deltaRaw * (360.0 / 4096.0);


    // ==========================================
    // 8. Velocidad angular
    // ==========================================
    //
    // RPS = (Δθ / 360) / Δt
    //
    float rps =
      (deltaAngle / 360.0) / deltaTime;


    // ==========================================
    // 9. RPM
    // ==========================================
    //
    // RPM = RPS * 60
    //
    rpm = rps * 60.0;


    // ==========================================
    // 10. Ángulo actual en grados
    // ==========================================
    //
    // Sólo para visualización
    //
    float currentAngle =
      rawAngle * (360.0 / 4096.0);


    // ==========================================
    // 11. Imprimir resultados
    // ==========================================
    Serial.print(rps, 2);
    Serial.print(",");

    Serial.print(rpm, 1);
    Serial.print(",");

    Serial.println(currentAngle, 2);
  }


  // ==========================================
  // 12. Guardar muestra actual
  // ==========================================
  lastRawAngle = rawAngle;
  lastTime = currentTime;

  sampleCount++;


  // ==========================================
  // 13. Frecuencia de muestreo
  // ==========================================
  //
  // 10 ms -> 100 Hz
  //
  delay(10);
}
