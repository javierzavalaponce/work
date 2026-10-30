
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