```{=latex}
\clearpage
```



# Sensores / encoders


## AS5600 Encoder Magnético 12 Bits

asfsdf

\begin{figure}[H]
\centering
\includegraphics[width=0.5\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/AS5600_pinout.png}
\caption{asdfasdf}
\label{fig:encoder0}
\end{figure}


| Board pin | Descripción |
|:---------|:------------|
| Vcc | Alim. (5 o 3.3)Vdc    | 
| Out | Salida Analógica o PWM|  
| Gnd | Gnd                   |
| Dir | Input: (GND o VDD), (incrementa o decrementa) clockwise  |
| SCL | Clk I2C - A4          |
| SDA | Data I2C - A5             |
| GPO | Input Pin de programación|

: Pinout

```c
void setup()
{
    Wire.setClock(100000); //Eso es 100 kHz, 
                           //Standard Mode de I²C.
    as5600.begin();
}
```

En arduino SDA  A4 , SCL  A5.




# PWM BS 

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
Modelado y simulación

## Pybullet

# Hardware 

# Implementación del controlador

# Implementación del observador

# Logging 

# Simulación contra experimento.


