### Control PI

Pregunta:

* ¿Qué tan lejos se está del objetivo?
* ¿Desde hace cuánto tiempo se está equivocado?

Y usa ambas cosas para corregir el sistema. Una analogía: imagine llenar un vaso con agua hasta una marca exacta:

* Si falta mucha agua, se abre más la llave, si falta poca, se abre menos la llave.

* Si pasa mucho tiempo y no se ha alcanzado la marca, se abre más la llave.

* Al llegar a la marca puede que se pase y que luego haya que corregir hacia atrás. Se entiende que no es un fracaso del control, sino una consecuencia manejable.


\begin{figure}[H]
\centering
\includegraphics[height=0.32\textheight,trim=0cm 2cm 0cm 2cm,clip]{./img/pi_a_bloques.pdf}
\caption{$C(s)=k_p+\frac{k_i}{s} = \frac{k_p s + k_i}{s}$ $\rightarrow$ introduce polo en el origen $s=0$ trayectoria cero en $s = -k_i/k_p$}
\label{fig:pi_a_blokes}
\end{figure}

En Laplace:

```{=latex}
\begin{equation}
\label{eq:controlador_pi}
\begin{aligned}
C(s)=k_p+\frac{k_i}{s} = \frac{k_p s + k_i}{s}
\end{aligned}
\end{equation}
```

O bien, con $k = k_p$ y $\alpha = (k_i/k_p)$


```{=latex}
\begin{equation}
\begin{aligned}
C(s)=\frac{k(s+\alpha)}{s}
\end{aligned}
\label{eq:pi_efecto}
\end{equation}
```


La ecuación \eqref{eq:controlador_pi} muestra que el controlador PI introduce un polo en el origen $s=0$
y también introduce un cero en $s = -k_i/k_p$



#### Ejemplo


Diseñar un controlador PI para que el sistema sea:

* Estable y
* Criticamente amortiguado

Función de transferencia de la planta: 

\begin{equation}
\begin{aligned}
G(s) = \frac{1}{s-3}
\end{aligned}
\end{equation}

Un PI añade un polo en el origen y un cero libre. De la ecuación \ref{eq:pi_efecto}, podemos arbitrariamente fijar el cero en $-1$ con $\alpha = 1$


```{=latex}
\begin{equation}
\begin{aligned}
C(s) = \frac{k(s+\alpha)}{s} = \frac{k(s+1)}{s}
\end{aligned}
\end{equation}
```

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 8cm 0cm 5cm,clip]{./img/ejemplo_PI.pdf}
\caption{Efecto del PI}
\label{fig:control_pi}
\end{figure}


Reduciendo los bloques	$ft = \frac{C(s)G(s)}{1+C(s)G(s)}$

```{=latex}
\begin{equation}
\begin{aligned}
ft = \frac{ \frac{k(s+1)}{s(s-3)}}{1 + \frac{k(s+1)}{s(s-3)}} = \frac{k(s+1)}{s(s-3)+k(s+1)}
\end{aligned}
\label{eq:pi_reduciendo}
\end{equation}
```

La nueva ecuación característica es:

```{=latex}
\begin{equation}
\begin{aligned}
s^2 - 3s  +ks + k = s^2 + (k-3)s + k = 0
\end{aligned}
\end{equation}
```

Las condiciones de estabilidad son

```{=latex}
\begin{equation}
\begin{aligned}
(k-3) > 0 \\
k > 0
\end{aligned}
\end{equation}
```
es decir, el sistema es estable para 

\begin{equation}
\boxed{k > 3}
\end{equation}



De la ecuación característica en \ref{eq:pi_reduciendo} , despejamos $k$ para encontrar el punto en que los polos 
se reintegran al eje real generando la condicion de **criticamente amortiguado**  $s$ real $< 0$

```{=latex}
\begin{equation}
\begin{aligned}
k = - \frac{s(s-3)}{s+1} = - \frac{s^2-3s}{s+1}
\end{aligned}
\end{equation}
```

Igualando la derivada de $k$ a cero, encontramos el punto donde las raíces dejan de ser complejas conjugadas y se unen nuevamente sobre el eje real.

```{=latex}
\begin{equation}
\begin{aligned}
\frac{dk}{ds} = -\frac{(2s-3)(s+1)-(s^2-3s)}{(s+1)^2}
\end{aligned}
\end{equation}
```

Igualando la derivada a cero, encontramos el punto donde las raíces
dejan de ser complejas conjugadas y se unen nuevamente sobre el eje real.

\begin{equation}
\begin{aligned}
\frac{dk}{ds} = 0
\end{aligned}
\end{equation}

Por lo tanto,

\begin{equation}
\begin{aligned}
(2s-3)(s+1)-(s^2-3s)=0
\end{aligned}
\end{equation}

Desarrollando,

\begin{equation}
\begin{aligned}
2s^2 - s - 3 - s^2 + 3s = 0
\end{aligned}
\end{equation}

\begin{equation}
\begin{aligned}
s^2 + 2s - 3 = 0
\end{aligned}
\end{equation}

Factorizando,

\begin{equation}
\begin{aligned}
(s+3)(s-1)=0
\end{aligned}
\end{equation}

Las soluciones son

\begin{equation}
\begin{aligned}
s=-3
\qquad
s=1
\end{aligned}
\end{equation}

Sin embargo, para que el sistema sea estable, los polos deben
permanecer en el semiplano izquierdo, por lo que únicamente
tomamos:

\begin{equation}
\boxed{s=-3}
\end{equation}

Sustituyendo en la ecuación de $k$:

\begin{equation}
\begin{aligned}
k = -\frac{(-3)(-3-3)}{-3+1}
\end{aligned}
\end{equation}

\begin{equation}
\begin{aligned}
k = -\frac{18}{-2}
\end{aligned}
\end{equation}

\begin{equation}
\boxed{k=9}
\end{equation}

Por lo tanto, el controlador

\begin{equation}
\boxed{
C(s)=\frac{9(s+1)}{s}
}
\end{equation}

produce un sistema estable y críticamente amortiguado.





\newpage
 