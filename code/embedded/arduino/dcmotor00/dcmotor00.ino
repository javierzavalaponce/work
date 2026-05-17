  // Arduino + AS5600 - Leer Revoluciones Por Segundo (RPS)
  // Librería: AS5600 de Rob Tillaart

  #include <Arduino.h>
  #include <Wire.h>
  #include <AS5600.h>

  AS5600 as5600;
const int IR_SENSOR_PIN = 9; 

    // Pines BTS7960
  const int RPWM = 5;
  const int LPWM = 6;
  const int R_EN = 7;
  const int L_EN = 8;


    void setup_read_infra() {
     //init pin 9 input
     pinMode(IR_SENSOR_PIN, INPUT);
    }
void infra(void)
    {
      static int ultimoEstado = HIGH;
      static int contador = 0;
      int estadoActual = digitalRead(IR_SENSOR_PIN);
     
      Serial.print("------- ");
      Serial.print(estadoActual);

    
    // Detectar flanco descendente (LOW cuando pasa objeto)
    if (ultimoEstado == HIGH && estadoActual == LOW) {
        contador++;
        Serial.print("Objetos contados: ");
        Serial.println(contador);
    }
    
    ultimoEstado = estadoActual;
    }

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


        
    setup_drivermotor();
    setup_read_infra();

    delay(100);

    return;
    Wire.begin();
    Wire.setClock(400000);
    as5600.begin();

    
    setup_drivermotor();
    setup_read_infra();

    delay(100);
    Serial.println("AS5600 RPS Reader Started");
    Serial.println("Format: RPS,RPM,Angle");
  }

  void loop() {

    static unsigned int i = 0;
    Serial.println("sgg");
    //infra();
    #ifdef ORIGINAL 
    int rawAngle = as5600.readAngle(); //[0,4095]
    unsigned long currentTime = micros();

    // ================================
    // 3. Ejecutar sólo después
    //    de tener una muestra previa
    // ================================
    if (sampleCount > 0) {

      int deltaRaw = rawAngle - lastRawAngle;
      
      // Corregir wrap-around: 4095 -> 0 | 0 -> 4095
      if      (deltaRaw < -2048)  { deltaRaw += 4096; }
      else if (deltaRaw >  2048)  { deltaRaw -= 4096; }

      float deltaTime = (currentTime - lastTime) / 1000000.0; // tiempo entre muestras
      float deltaAngle =  deltaRaw * (360.0 / 4096.0); // Convertir RAW -> grados
       //Velocidad angular
      float rps = (deltaAngle / 360.0) / deltaTime; 
      rpm = rps * 60.0; //RPM

      float currentAngle = rawAngle * (360.0 / 4096.0); //para visualización

      Serial.print(rps, 2); Serial.print(",");
      Serial.print(rpm, 1); Serial.print(",");
      Serial.println(currentAngle, 2);
    }

    // Guardar muestra actual
    lastRawAngle = rawAngle;
    lastTime = currentTime;
    sampleCount++;
    #endif
    delay(100); //Frecuencia de muestreo (100Hz)
  }
    