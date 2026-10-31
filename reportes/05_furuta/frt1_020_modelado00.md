```{=latex}
\clearpage
```

# Modelado 


| Parámetro          | Símbolo y significado |
|:-------------------|:----------------------|
| $L_1 = 237 mm$   | longitud  del brazo horizontal|
| $L_2 = 220 mm$   | longitud  del péndulo |
| $l_1 = 150 mm$ | distancia del eje de giro al centro de masa del brazo |
| $l_2 = 125 mm$ | distancia del eje de giro al centro de masa del péndulo |
| Masa  $m_1 = 200 gramos$ |masa del brazo |
| Masa  $m_2 = 220 gramos$ | masa del péndulo. |
| Inercias           | $J_1$, $J_2$, momentos de inercia |
| Fricción           | $b_1$, $b_2$, coeficientes de amortiguamiento |
| Gravedad           | $g$, ($\approx 9.81\,\text{m/s}^2$) |

: Parámetros del péndulo de Furuta

\begin{figure}[H]
\centering
\includegraphics[width=0.91\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/fur_convencion.png}
\caption{Parametros}
\label{fig:ilustfur021}
\end{figure}


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

\newpage

### Cinemática


El sistema tiene 2 grados de libertad: 
$$
q = \begin{bmatrix} \theta_1 \\ \theta_2 \end{bmatrix}
$$

**$\theta_1$ (Ángulo del brazo).** Es el ángulo de rotación horizontal del brazo con respecto al eje $x$. Si $\theta_1  = 0$, el brazo apunta al semieje positivo $x$.

**$\theta_2$ (Ángulo del péndulo).** Se mide respecto al eje vertical $z$, tomando como referencia la dirección vertical hacia abajo. Cuando $\theta_2=0$, el péndulo está completamente vertical apuntando hacia abajo (posición estable). Cuando $\theta_2=\pi\ (180^\circ)$, el péndulo está completamente vertical apuntando hacia arriba (posición invertida o inestable). Cuando $\theta_2=90^\circ$ el péndulo apunta hacia $+y$.

#### Posición de un punto sobre el péndulo

El péndulo oscila en un plano vertical perpendicular al brazo.  Cuando 
$\theta_1 = 0$ , el brazo apunta en $+x$ y el péndulo se mueve en el plano $yz$. 
Para el péndulo (masa $m_2$, centro a distancia $l_2$ del pivote):

\begin{figure}[H]
\centering
\includegraphics[width=0.59\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/fur_ilust03.png}
\end{figure}

\newpage
Las ecuaciones siguientes corresponden a una convención en la que:

* $\theta_1$ positivo gira alrededor de $+z$
* $\theta_2$ positivo gira alrededor del eje local $+x$ del brazo
* El péndulo parte de $-z$

```{=latex}
\[
\begin{aligned}
x_2 &= L_1 \cos\theta_1 - l_2 \sin\theta_2 \sin\theta_1 \\
y_2 &= L_1 \sin\theta_1 + l_2 \sin\theta_2 \cos\theta_1 \\
z_2 &= -l_2 \cos\theta_2
\end{aligned}
\]
```

### Dinámica

(draft)
masas
inercias
fricción...


