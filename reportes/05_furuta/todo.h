
Todo.h

notas imprecisas (revisar):

Para el péndulo de Furuta: el modelo mecánico físico no contiene retardo, 
pero el sistema de control del lazo cerrado debe modelarse como un "sistema de retardo". Ignorar el retardo de muestreo en el diseño del controlador puede causar un fracaso completo en el experimento real; por el contrario, al analizar teóricamente, la ecuación característica del péndulo de Furuta con control retardado se convierte en una ecuación cuasi-polinomial que contiene términos exponenciales de retardo


git clone https://github.com/AngeloDamante/Furuta_pendulum.git



------------------------
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

(draft)
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


#### URDF y ROS

(draft)
En el mundo ROS es muy importante:
URDF — Unified Robot Description Format
Es un formato XML para describir robots mediante links y joints
Es muy útil para simulación y ROS, pero no es "el estándar universal de los robots industriales".
8484: lagunas conceptuales aqui...
\newpage

#### URDF y ROS

(draft)
\newpage


* ISR mínima + variables de estado
* Lazo de control periódico
* Prioridad temporal de cada tarea


definir arquitectura...

¿Cómo funcionan exactamente PCINT0, PCINT1 y PCINT2 y cuántas ISR reales tiene el ATmega328P?



El as5600 se comunica por12c
es absoluto ? que pasa con el 0?

el encoder incremental isr pd2 y pd3 A y b
logs via serial
fifos?

En robótica, online/offline se refiere principalmente a si se esta interactuando directamente con el robot físico o trabajando sin él.


## Offline  

Control manual


## Online

El robot online necesita el sw
```drive_fur``` 
que es un programa hecho en python
envia comandos via serial al 
arduino 
para interactuar 

---
TCP Tool Center Point

Frame sistema de coordenadas

Base frame sistema de coordenadas de la base

Tool frame

Joints / joint space
espacio articular

Cartesian space
espacio cartesiano

Forward kinematics (FK)
cinemática directa

Inverse kinematics (IK)
cinemática inversa

Jogging
mover manualmente los ejes

Teach pendant

Controller

Post processor

Robot driver

OLP — Offline Programming

Collision checking

Reachability

Singularity

Path planning


El flujo:

modelo → joints → frames → TCP → FK → IK → trayectoria → simulación → postprocesador → controlador → robot físico.

Ese es prácticamente el idioma conceptual del área.
