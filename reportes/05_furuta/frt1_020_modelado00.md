```{=latex}
\clearpage
```
	
# Modelado 


## Modelo del Pendulo de Furuta (geometria Openscad)

Revisar / completar

| Parámetro          | Símbolo y significado |
|:-------------------|:----------------------|
| $L_1$   | longitud  del brazo horizontal|
| $L_2$   | longitud  del péndulo. |
| Centro de masa   $l_1$ | distancia del eje de giro al centro de masa de cada eslabón. |
| Centro de masa   $l_2$ | distancia del eje de giro al centro de masa de cada eslabón. |
| Masa  $m_1$ |masa del brazo |
| Masa  $m_2$ | masa del péndulo. |
| Inercias           | $J_1$, $J_2$, momentos de inercia efectivos. |
| Fricción           | $b_1$, $b_2$, coeficientes de amortiguamiento viscoso. |
| Gravedad           | $g$, aceleración gravitacional ($\approx 9.81\,\text{m/s}^2$). |

: Parámetros del péndulo de Furuta

### $b_1$ y $b_2$ : Coeficientes de fricción viscosa

La fricción viscosa es una fuerza (o torque) de resistencia proporcional a la velocidad. 
Modela el roce en los rodamientos, Matemáticamente:

$$
= - b \dot {\theta}
$$

$b$ es el coeficiente y $\dot{\theta}$  la velocidad angular. 
El signo negativo indica que se opone al movimiento.

*$b_1$*: Fricción viscosa en el eje del brazo ($\theta_1$)

Representa el torque de resistencia que siente el motor al girar el brazo. 
Incluye: 1. Roce en los rodamientos del eje vertical.
2. Roce interno del motor (a veces se separa, pero aquí se agrupa).
3. Resistencia aerodinámica del brazo (pequeña).

Unidades: $\text{N}\,\text{m}\,\text{s}/\text{rad}$ (torque por unidad de velocidad angular).

*$b_2$*: Fricción viscosa en el pivote del péndulo  ($\theta_2$)

Representa el torque de resistencia en la articulación entre el péndulo y el brazo:

Roce en el rodamiento de esa unión.
Resistencia del aire sobre el péndulo (proporcional a su velocidad angular).

$b_1$ y $b_2$ se obtienen experimentalmente: 
se deja oscilar y se ajusta la curva de decaimiento de la amplitud.

 

\newpage
```c
// furuta3.scad
// ==================== PARÁMETROS ====================
armlength = 237;
baselength = 232;
L_pendulo = 220;    
   
L_peso = 30;              
r_peso = 15;
r_varilla = 5;

pared = 2;
diam_tubo_arm = 19;
radio_ext = diam_tubo_arm / 2;
radio_int = radio_ext - pared;

// péndulo de Furuta
// furuta3.scad
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

//pendulo a 40 grados de la vertical
furuta(10,40);
```
\newpage

### Cinemática


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

