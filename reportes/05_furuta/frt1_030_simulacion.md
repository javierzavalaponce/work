```{=latex}
\clearpage
```
	
# Simulación


# Analisis Inicial


El péndulo de Furuta es un benchmark estándar para validar controladores. En su implementación real, el lazo de control es digital, lo que introduce un retardo de un ciclo de muestreo entre la medición del estado y la aplicación del voltaje al motor. La literatura demuestra que este retardo impone un límite máximo al tiempo de muestreo (tiempo crítico) y puede desestabilizar el sistema incluso con ganancias óptimas. Propongo diseñar un controlador (LQR o Modos Deslizantes) que incorpore explícitamente este retardo en su diseño (por ejemplo, mediante un margen de retardo garantizado o un modelo discreto), en lugar de ignorarlo, y validarlo experimentalmente."


## Vista No Lineal 

El péndulo es un sistema *no lineal*. Se puede "ver" usando su modelo dinámico (Euler-Lagrange). 
Posibilidad de centrarse en control no lineal (ej. modos deslizantes, Lyapunov) .

## Vista Lineal 

Se "linealiza" el modelo alrededor del punto de equilibrio inestable (arriba). 
se hace realizaxion de sistema de espacio de estados 
$\dot{x}= Ax + Bu$ . Es el enfoque estándar para LQR, ubicación de polos o PID .

## Vista Híbrida 

El problema se divide en dos fases: Swing-up (llevar el péndulo de abajo hacia arriba, usualmente con control de energía) y Balanceo (estabilizarlo arriba, con control lineal o no lineal).
 Muchos trabajos proponen un conmutador entre ambas estrategias .

## Dónde aparece exactamente el retardo

Ocurre en este orden:

Se mide el ángulo del péndulo ($\theta_1$) y la velocidad del brazo ($\dot{\theta_2}$) en un instante $t_j$

El uC alcula la señal de control (el voltaje U (activacion del puente H)) con esos datos.

 El motor recibe y aplica esa señal pero no instantáneamente. La aplica un tiempo después, en $t_{j+1}$.

Es decir: la señal de control que se aplica en el intervalo $[tj,tj+1)$
se calcula usando los datos medidos en el instante anterior, 
$t_{j−1}$. 

Es decir, hay un retardo de un ciclo de muestreo completo entre el momento en que se registra el estado del péndulo y el momento en que la acción correctiva surte efecto en el motor.


La formulación Euler-Lagrange es el estándar para obtener el modelo no lineal del Furuta . Para el diseño del controlador, linealizamos alrededor del equilibrio inestable y obtenemos un modelo en espacio de estados . Mi propuesta añade un bloque de retardo $e^{-s\tau}$
en la trayectoria de control, porque en la implementación digital real la señal se aplica con un ciclo de retraso. El objetivo es diseñar un controlador que garantice estabilidad para un $\tau$ máximo conocido.

Aqui la forma estándar del modelo no lineal del Furuta:

```{=latex}
\begin{equation}
M(q)\ddot{q} + C(q,\dot{q})\dot{q} + G(q) = F u
\label{eq:furuta_matricial}
\end{equation}
```

Esta ecuacion sale de Euler-Lagrange. Cada término tiene un origen físico: 

* $M(q)$ es la inercia, depende de $q$ porque la inercia efectiva cambia según la posición del péndulo.
* $C(q,\dot{q}$ son Coriolis y centrífugos, que dependen de la posición (geometría) y de las velocidades (efectos dinámicos)
* $G(q)$ es la gravedad, que solo depende de la posición
* $F$  es la acción del motor.



