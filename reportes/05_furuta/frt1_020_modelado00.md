```{=latex}
\clearpage
```
	
# Modelado 

: Tabla 1. Pruebas para caracterizar el motor del péndulo de Furuta.

| Prueba | ¿Qué medir? | ¿Para qué sirve? |
| :--- | :--- | :--- |
| **Prueba de Torque Estático** | Fuerza en el extremo del brazo (con una balanza) para diferentes voltajes/PWM. | Calcula el **torque máximo** disponible en el eje de salida (brazo). Es crucial para saber si puedes vencer la gravedad y la inercia del péndulo. |
| **Prueba de Velocidad en Vacío** | Velocidad angular máxima (RPM) del brazo sin carga, para tu voltaje máximo. | Determina la **velocidad máxima** que puedes transmitir al péndulo. Aquí es donde tu sospecha de insuficiencia puede confirmarse o descartarse. |
| **Prueba de Respuesta al Escalón** | Curva de velocidad vs. tiempo al aplicar un voltaje de entrada repentino. | Te permite identificar la **constante de tiempo** del sistema (qué tan rápido acelera) y estimar la inercia total del conjunto motor-reducción-brazo. |
| **Identificación de Parámetros** | Mediciones de voltaje y corriente durante una prueba de escalón de velocidad. | Puedes usar estos datos para calcular parámetros eléctricos como la **resistencia (R)** y la **constante de fuerza contraelectromotriz (Ke)** del motor. |


ver /doc/modelado_motor.pdf

tambien ver el

git clone https://github.com/AngeloDamante/Furuta_pendulum.git



\newpage

