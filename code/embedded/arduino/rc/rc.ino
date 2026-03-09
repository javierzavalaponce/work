float y = 0.0;
float x = 5.0; // Aplica escalon de 5 Volts

float RC = 0.1;
float Ts = 0.002;

unsigned long last = 0;

void setup()
{
    Serial.begin(115200);
}

void loop()
{   //toma una muestra cada 2 ms 
    if (micros() - last >= 2000)
    {       
        last = micros();
        y = y + (Ts/RC)*(x - y);
        Serial.println(y);
    }
}

