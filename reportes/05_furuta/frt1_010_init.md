```{=latex}
\clearpage
```
	
# Introducción


 El Péndulo de Furuta fue inventado en 1992 en el Instituto de Tecnología de Tokio por Katsuhisa Furuta. También se le conoce como Péndulo Invertido Rotacional
  (Rotational Inverted Pendulum).

Tiene dos partes mecánicas clave:

1. Brazo horizontal (Brazo 1): Conectado directamente a un motor eléctrico. Gira en el plano horizontal (color naranja)

2. Péndulo vertical (Brazo 2): Conectado al extremo del brazo 1 mediante un eje libre. Gira en el plano vertical. No tiene motor (color gris).


 El Péndulo de Furuta es un sistema subactuado (underactuated):

 * Tiene 2 grados de libertad (el ángulo del brazo $\theta_1$ y el ángulo del péndulo $\theta_2$).
 * Pero sólo tiene 1 motor (actuador en $\theta_1$).
 * El brazo se debe hacer rotar con la aceleración exacta para que las fuerzas de inercia, centrífuga y de Coriolis muevan el péndulo a donde se desea.

* Es altamente no lineal (non-linear). Aparecen fuerzas gravitatorias dependientes del seno y coseno.
  Cuando el brazo gira rápido, la fuerza centrífuga empuja al péndulo hacia afuera, y la fuerza de Coriolis acopla el movimiento de ambos brazos.

 \newpage

| Parámetro          | Símbolo y significado |
|:-------------------|:----------------------|
| Ángulo del brazo   | $\theta_1$, posición angular del brazo en el plano horizontal. |
| Ángulo del péndulo | $\theta_2$, inclinación vertical del péndulo ($0$ = hacia abajo en reposo, $\pi$ = vertical invertido). |
| Torque del motor   | $\tau_1$, fuerza de giro que inyecta tu motor DC al brazo 1. |
| Longitudes         | $L_1$, $L_2$, longitud total del brazo horizontal y del péndulo. |
| Centros de masa    | $l_1$, $l_2$, distancia del eje de giro al centro de masa de cada eslabón. |
| Masas              | $m_1$, $m_2$, masa del brazo y masa del péndulo. |
| Inercias           | $J_0$, $J_2$, momentos de inercia efectivos. |
| Fricción           | $b_1$, $b_2$, coeficientes de amortiguamiento viscoso. |
| Gravedad           | $g$, aceleración gravitacional ($\approx 9.81\,\text{m/s}^2$). |

: Parámetros del péndulo de Furuta

\begin{figure}[H]
\centering
\includegraphics[width=0.92\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/fur_00.png}
\caption{Brazos y angulos del pendulo de Furuta.}
\label{fig:Partes}
\end{figure}




\newpage

notas, ver:

/doc/modelado_motor.pdf

git clone 
https://github.com/AngeloDamante/Furuta_pendulum.git

\newpage

