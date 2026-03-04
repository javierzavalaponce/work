float y = 1.0;        // condición inicial
float t = 0.0;
float h = 0.05;       // paso de integración

void setup() {
  Serial.begin(115200);
}

void loop() {

  // imprimir tiempo y valor
  Serial.print(t);
  Serial.print(",");
  Serial.println(y);

  // Método de Euler
  float dydt = -2.0 * y;
  y = y + h * dydt;
  t = t + h;

  delay(50);  // solo para visualizar más lento
}

