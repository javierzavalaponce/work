```{=latex}
\clearpage
```
	
# Modelado 

: Tabla 1. Pruebas para caracterizar el motor del péndulo de Furuta.

| Prueba | ¿Qué medir? | ¿Para qué sirve? |
| :--- | :--- | :--- |
| **Prueba de Torque Estático** | Fuerza en el extremo del brazo (con una balanza) para diferentes voltajes/PWM. | Calcula el **torque máximo** disponible en el eje de salida (brazo). Es crucial para saber si puedes vencer la gravedad y la inercia del péndulo. |
| **Prueba de Velcoidad en Vacío** | Velocidad angular máxima (RPM) del brazo sin carga, para tu voltaje máximo. | Determina la **velocidad máxima** que puedes transmitir al péndulo. Aquí es donde tu sospecha de insuficiencia puede confirmarse o descartarse. |
| **Prueba de Respuesta al Escalón** | Curva de velocidad vs. tiempo al aplicar un voltaje de entrada repentino. | Te permite identificar la **constante de tiempo** del sistema (qué tan rápido acelera) y estimar la inercia total del conjunto motor-reducción-brazo. |
| **Identificación de Parámetros** | Mediciones de voltaje y corriente durante una prueba de escalón de velocidad. | Puedes usar estos datos para calcular parámetros eléctricos como la **resistencia (R)** y la **constante de fuerza contraelectromotriz (Ke)** del motor. |


ver /doc/modelado_motor.pdf

tambien ver el

git clone https://github.com/AngeloDamante/Furuta_pendulum.git


## Modelo del Pendulo de Furuta

### Geometría

modelos CAD 3d
dimensiones
apariencia

### Cinemática

articulaciones
ejes
dimensiones
límites
transformaciones

Base-J1-Link 1-J2-Link 2-J3

Para cada articulación puede haber información como:
* tipo: revoluta/prismática
* eje de movimiento
* posición relativa
* orientación
* límites
* relación entre articulaciones y eslabones

matrices de transformación, coordenadas, DH, cinemática directa e inversa.


dimensiones cinemáticas en forma de tablas ***Denavit-Hartenberg***

### Dinámica

masas
inercias
fricción...
Si además queremos simular físicamente el robot, aparecen:
* masa
* centro de masa
* tensor de inercia
* fricción
* amortiguamiento
* límites de esfuerzo/torque

Por ejemplo, **URDF** puede representar explícitamente masa, centro de masa e inercias de cada link, además de propiedades de las articulaciones.

Esto es diferente de la simple cinemática.

#### URDF y ROS

En el mundo ROS es muy importante:
URDF — Unified Robot Description Format
Es un formato XML para describir robots mediante links y joints
Es muy útil para simulación y ROS, pero no es "el estándar universal de los robots industriales".
8484: lagunas conceptuales aqui...
\newpage

