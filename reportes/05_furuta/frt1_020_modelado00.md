```{=latex}
\clearpage
```
	
# Modelado 

notas imprecisas (revisar):

Para el péndulo de Furuta: el modelo mecánico físico no contiene retardo, pero el sistema de control del lazo cerrado debe modelarse como un "sistema de retardo". Ignorar el retardo de muestreo en el diseño del controlador puede causar un fracaso completo en el experimento real; por el contrario, al analizar teóricamente, la ecuación característica del péndulo de Furuta con control retardado se convierte en una ecuación cuasi-polinomial que contiene términos exponenciales de retardo


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


\newpage

## Modelo del Pendulo de Furuta (geometria Openscad)

### Geometría

Revisar / completar

| Parámetro          | Símbolo y significado |
|:-------------------|:----------------------|
| $L_1$   | longitud  del brazo horizontal|
| $L_2$   | longitud  del péndulo. |
| Centro de masa   $l_1$ | distancia del eje de giro al centro de masa de cada eslabón. |
| Centro de masa   $l_2$ | distancia del eje de giro al centro de masa de cada eslabón. |
| Masa  $m_1$ |masa del brazo |
| Masa  $m_2$ | masa del péndulo. |
| Inercias           | $J_0$, $J_2$, momentos de inercia efectivos. |
| Fricción           | $b_1$, $b_2$, coeficientes de amortiguamiento viscoso. |
| Gravedad           | $g$, aceleración gravitacional ($\approx 9.81\,\text{m/s}^2$). |

: Parámetros del péndulo de Furuta

Modelo Openscad 

\newpage
```c

// ==================== PARÁMETROS ====================
L_pendulo = 225;          
L_peso = 30;              
r_peso = 15;
r_varilla = 5;

armlength = 237;
baselength = 237;
pared = 2;
diam_tubo_arm = 19;
radio_ext = diam_tubo_arm / 2;
radio_int = radio_ext - pared;

// ==================== MÓDULOS ====================


// Brazo: se extiende a lo largo del eje Y positivo
module arm(){
    rotate([90, 0, 0]) {
        difference(){
            cylinder(h=armlength, r=radio_ext, center=false);
            cylinder(h=armlength + 2, r=radio_int, center=false);
        }
    }
}



// Péndulo: su PIVOTE está en el origen (parte superior de la varilla)
module pendulo(angulo){
    rotate([0, -angulo, 0]) { 
        // Gira alrededor del eje Y (eje del brazo)
        // Varilla (baja desde 0 hasta -225)
        translate([0, 0, -L_pendulo])
        cylinder(h=L_pendulo, r=r_varilla, center=false);
        // Peso (situado a 15mm del extremo)
        translate([0, 0, -210])
        cylinder(h=L_peso, r=r_peso, center=false);
    }
}


module base(){
    union(){
    cylinder(h=50, r=30, center=false);
    cylinder(h=baselength, r=16, center=false);

    }
}



// Sistema completo del péndulo de Furuta
module furuta(theta, alpha){
    color("#6F1D46")       // Rojo vino 
    translate([0, 0,-baselength])
    base();
    // 1. Rotación del brazo en el plano horizontal
    rotate([0, 0, theta]) { 
        color("orangered")
        arm();                       
        color("gray")
        translate([0,-armlength, 0]) { 
            pendulo(alpha);      
        }
    }
}


furuta(10,40);

```
\newpage

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

