```{=latex}
\clearpage
```

# Modulos, sensores y encoders


## AS5600 Encoder Magnético 12 Bits

\begin{figure}[H]
\centering
\includegraphics[width=0.4\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/AS5600_pinout.png}
\caption{asdfasdf}
\label{fig:encoder0}
\end{figure}


| Board pin | Descripción |
|:---------|:------------|
| Vcc | Alim. (5 o 3.3)Vdc    | 
| Out | Salida Analógica o PWM|  
| Gnd | Gnd                   |
| Dir | Input: (GND o VDD), (incrementa o decrementa) clockwise  |
| SCL | Clk I2C - Arduino uno A4          |
| SDA | Data I2C - Arduino uno A5             |
| GPO | Input Pin de programación|

: Pinout

\vspace{1cm}


```c
void setup()
{
    Wire.setClock(100000); //Eso es 100 kHz, 
                           //Standard Mode de I²C.
    as5600.begin();
}
```

\newpage

## DC Motor Driver BTS7960

El BTS7960 Driver Puente H 43A es un modulo para controlar motores DC
(hasta 43A en picos). Cuenta con aislamiento y protección hacia microcontrolador.  Tiene 8 pines de control


| Board pin | Descripción |
|:---------|:------------|
| 7 Vcc | Alim. Vcc | 
| 5 R_IS | Ard. A0 Right analog i sense |  
| 3 R_EN | Ard. 7 Right enable                   |
| 1 R_PWM | Ard ~5. Dig pin. Right pwm. Verde|
| 8 Gnd | Gnd mismo nodo bat(?)|
| 6 L_IS | Ard. A1 Right analig i sense |
| 4 L_EN | Ard. 8 Left Enable|
| 2 L_PWM| Ard ~6 Dig pin. Left pwm . Blanco|

: Pinout DC motor driver	


\begin{figure}[H]
\centering
\includegraphics[width=0.42\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/bts_7960.png}
\caption{asdfasdf}
\label{fig:bts_}
\end{figure}

Pines $R_{PWM}$ (Right PWM) y $L_{PWM}$ (Left PWM) no son  *vel. derecha* y *vel. izquierda*. En realidad controlan cada uno de los dos lados del puente H. Para hacer girar el motor en un sentido, normalmente activas una entrada PWM y mantienes la otra en LOW.

$R_{EN}$ y $L_{EN}$ del BTS7960 no controlan la velocidad; sirven para habilitar o deshabilitar cada mitad del puente H.


```c
// Mecanismo sugerido de seguridad
if (corriente > limite) {
    digitalWrite(R_EN, LOW);
    digitalWrite(L_EN, LOW);
}
```

```c
// ejemplo de init.
void setup_drivermotor() {
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
}
```



\newpage

## Leds Auxiliares


| Arduino pin | led  |
|:---------|:------------|
| Ard pin 12 | led2 | 
| Ard pin 4  | led1 | 

: Leds auxiliares

\newpage

## Encoder Incremental  

Encoder Incremental 600 Pulsos LPD3806-600BM 5-24V DC. Dispositivo electromecánico que convierte el movimiento de un eje rotatorio en señales eléctricas digitales. Funciona mediante un disco ranurado y un sistema óptico interno que genera 600 pulsos por cada vuelta completa del eje, lo que permite medir con precisión la velocidad, posición y dirección de giro. 

\begin{figure}[H]
\centering
\includegraphics[width=0.62\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/encoder_incremental.png}
\caption{asdfasdf}
\label{fig:enco_incr}
\end{figure}


| LPD3806 | Arduino |
|:---------|:------------|
| Rojo | Alim. 5Vdc    | 
| Black | gnd |  
| Green | Arduino pin D3 - A     |
| White | Arduino pin D2 -B|

: Pinout


* Shaft 6mm.
* 600 pulsos por revolución
* Alimentación: 5–24 V DC
* Salidas: A y B

Las salidas A y B están desplazadas 90° eléctricamente
Salida tipo NPN open collector. Las dos señales permiten determinar: Cuánto ha girado el eje, qué tan rápido gira
y en qué sentido.

señal en cuadratura. con desfase de 90 grados 
ARduino puede dar pull up intrno

```c
//inspiracion
const int ENC_A = 2;
const int ENC_B = 3;

void setup()
{
    Serial.begin(115200);

    pinMode(ENC_A, INPUT_PULLUP);
    pinMode(ENC_B, INPUT_PULLUP);
}

void loop()
{
    int A = digitalRead(ENC_A);
    int B = digitalRead(ENC_B);

    Serial.print("A = ");
    Serial.print(A);

    Serial.print("  B = ");
    Serial.println(B);

    delay(10);
}
//con isr
attachInterrupt(
    digitalPinToInterrupt(ENC_A),
    encoderISR,
    RISING
);
//y entonces:
volatile long contador = 0;

void encoderISR()
{
    if (digitalRead(ENC_B) == HIGH)
        contador++;
    else
        contador--;
}

```
\newpage

## Encoder Incremental Rotativo p ctrl manual

El Encoder Incremental Rotativo EC11 es capaz de codificar salidas hacia la izquierda y hacia la derecha, tiene 20 retenciones perceptibles al tacto, puede girar 360° de forma continua y genera pulsos de salida digitales que ayudan a determinar la dirección y rotación , también cuenta con un interruptor el cual se acciona al presionar el eje del enconder. 

Led para monitores pin 12 arduino

| Board pin | Descripción |
|:---------|:------------|
| switch | switch Ard pin 11| 
| gnd | gnd |  
| Out A | encoder pin A verde Ard 9|
| gnd | gnd|
| Out B | encoder pin A verde Ard 10|

: Encoder para control manual


\begin{figure}[H]
\centering
\includegraphics[width=0.62\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/encoder_incr_rotativo.png}
\caption{asdfasdf}
\label{fig:enco_incr_rot}
\end{figure}



# Modelado y simulación

## Pybullet

# Hardware 

# Implementación del controlador

# Implementación del observador

# Logging 

# Simulación contra experimento.


