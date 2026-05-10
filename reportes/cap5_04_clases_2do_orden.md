### Sistemas de segundo orden

La ecuación (la forma canónica) de la función de transferencia de un sistema de segundo orden se escribe como:

```{=latex}
\begin{equation}
\begin{aligned}
G(s)=\frac{\omega_n^2}{s^2+2\zeta\omega_n s+\omega_n^2}\end{aligned}
\end{equation}
```

Sus polos son:
\
```{=latex}
\begin{equation}
\begin{aligned}
s = -\zeta \omega_n \pm j\,\omega_n \sqrt{1 - \zeta^2}
\end{aligned}
\end{equation}
```
\

* La ecuación característica define los polos

* Los polos definen el comportamiento del sistema



\newpage

### Especificaciones del transitorio para sistemas subamortiguados

\begin{figure}[H]
\centering
\includegraphics[height=0.40\textheight]{./img/segundo_orden.png}
\caption{Respuesta temporal de un sistema de 2do orden}
\end{figure}


* $M_p$: Maximo pico o punto de sobretiro.

* $T_p$: El tiempo pico es el instante en el que la respuesta alcanza su valor máximo por primera vez: $T_p = \frac{\pi}{\omega_d}$ ,  donde: $\omega_d = \omega_n \sqrt{1-\zeta^2}$

* $T_s$: El tiempo de *establecimiento*  se define como el instante a partir del cual la respuesta permanece dentro de una banda cercana al valor final y ya no vuelve a salir.




\newpage

### root locus. 2do orden

**Ejemplo:** Sea el siguiente sistema en lazo abierto, estudiar control por retroalimentación estatica de la salida. 

```{=latex}
\begin{equation}
\begin{aligned}
G(s) = \frac{1}{s^2 + 4s + 1}
\end{aligned}
\end{equation}
```

Control por retroalimentación estatica de la salida:

\begin{figure}[H]
\centering
\includegraphics[width=0.5\textwidth,trim=0cm 7cm 0cm 4cm,clip]{./img/root_locus_bloques.pdf}
\caption{analisis de LGR | root locus}
\label{fig:root_locus_bloques}
\end{figure}


La nueva funcion de transferencia en lazo cerrado es 

```{=latex}
\begin{equation}
\begin{aligned}
\frac{kG(s)}{1+kG(s)}  = \frac{k}{s^2 + 4s + (1+k)}
\end{aligned}
\end{equation}
```

En un sistema de segundo orden, los signos de los coeficientes  de la ec. característica permiten saber en qué lado del plano complejo estarán las raíces. Una **condición necesaria** para estabilidad es que todos los coeficientes deben tener el mismo signo (normalmente positivos).

En este caso, el sistema es estable ya que (aplicando la formula general) los polos estan en $s = -2 \pm \sqrt{3-k}$

```julia
using ControlSystems
using Plots

s=tf("s")
G = tf([1], [1, 4, 1])
println(pole(G))
p = rlocusplot(G)
savefig(p, "root_locus2do_orden.png")
```
Con $k=0$ se tiene un sistema estable  ya que ambos polos son reales negativos en semiplano izquierdo. 
$s_1 =-0.26$
$s_2 =-3.73$

```c

julia> pole(G)
 -0.26
 -3.73
julia> pole(feedback(1*G))
 -0.58
 -3.41
julia> pole(feedback(2.5*G))
 -1.29
 -2.70
julia> pole(feedback(3*G))
 -2.0
 -2.0
julia> pole(feedback(10*G))
 -1.99 + 2.64i
 -1.99 - 2.64i
julia> pole(feedback(100*G))
 -2.0 + 9.84i
 -2.0 - 9.84i
```

\begin{figure}[H]
\centering
\includegraphics[height=0.3\textheight]{./img/root_locus2do_orden.png}
\caption{Root locus: en s= -2 los polos se fusionan}
\end{figure}

\newpage

\begin{figure}[H]
\centering
\includegraphics[height=0.5\textheight]{img/step_overlap.png}
\caption{Respuesta al escalón con diferente k}
\end{figure}

El root locus dibuja cómo se mueven los polos del sistema cuando la ganancia $k$ aumenta desde 0 hasta infinito. Cuando la ganancia es pequeña, los polos están cerca de los polos del sistema en lazo abierto (los puntos de partida). Cuando 
$k$ crece, se mueven por el plano complejo.

\newpage

