```{=latex}
\clearpage
```

# Modelado 

## Modelo del Pendulo de Furuta (vista Openscad)

\begin{figure}[H]
\centering
\includegraphics[width=0.82\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/fur_convencion.png}
\caption{Parametros}
\label{fig:ilustfur021}
\end{figure}

\newpage 

| Parámetro          | Símbolo y significado |
|:-------------------|:----------------------|
| $L_1 = 237mm$   | longitud  del brazo horizontal|
| $L_2 = 220mm$   | longitud  del péndulo |
| $l_1 = 125mm$ | distancia del eje de giro al centro de masa del brazo |
| $l_2 = 127mm$ | distancia del eje de giro al centro de masa del péndulo |
| Masa  $m_1 = 200 gramos$ |masa del brazo |
| Masa  $m_2 = 220 gramos$ | masa del péndulo. |
| Inercias           | $J_1$, $J_2$, momentos de inercia |
| Fricción           | $b_1$, $b_2$, coeficientes de amortiguamiento |
| Gravedad           | $g$, aceleración gravitacional ($\approx 9.81\,\text{m/s}^2$) |

: Parámetros del péndulo de Furuta

### $b_1$ y $b_2$ : Coeficientes de fricción viscosa ($= - b \dot {\theta}$)

Modela fricción en los rodamientos. El signo negativo indica que se opone al movimiento.

**$b_1$**: Fricción viscosa en el eje del brazo ($\theta_1$)

Representa el torque de resistencia que siente el motor al girar el brazo. 
Incluye el roce en los rodamientos del eje vertical y la resistencia aerodinámica del brazo.
Sus unidades son: $\text{N}\,\text{m}\,\text{s}/\text{rad}$ (torque por unidad de velocidad angular).

**$b_2$**: Fricción viscosa en el pivote del péndulo  ($\theta_2$)

Representa el torque de resistencia en la articulación entre el péndulo y el brazo:

(315: Revisar / Consultar Docs)
$b_1$ y $b_2$ se obtienen experimentalmente: 
se deja oscilar y 
se ajusta la curva de decaimiento de la amplitud.


### Cinemática


El sistema tiene 2 grados de libertad: 
$$
q = \begin{bmatrix} \theta_1 \\ \theta_2 \end{bmatrix}
$$

$\theta_1$ (Ángulo del brazo). Es el ángulo de rotación horizontal del brazo con respecto al eje $x$. Si $\theta_1  = 0$, el brazo apunta al semieje positivo $x$.

$\theta_2$ (Ángulo del péndulo). Se mide con respecto al eje vertical $z$ . Cuando $\theta_2 = 0$, el péndulo está completamente vertical apuntando hacia arriba (posición invertida o inestable). Cuando $\theta_2 = \pi (180^\circ)$, el péndulo está colgando vertical hacia abajo (posición estable).

#### Parámetros físicos

* Mástil central:
    * Inercia de rotación alrededor del eje $z$: $J$.

* Brazo horizontal (eslabón 1):
    * Longitud: $L_1$ 
    * Masa: $m_1$ 
    * Coordenada radial de un punto sobre el brazo: $r_1 \in [0, L_1]$

* Péndulo (eslabón 2):
    * Longitud: $L_2$
    * Masa: $m_2$, centro de masa colocada cerca de la punta del péndulo $l_2$ 
    * Coordenada radial de un punto sobre el péndulo: $r_2 \in [0, L_2]$



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

