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


Diseñar un controlador PI para el siguiente sistema sea 

* Estable y
* Criticamente amortiguado

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


\newpage
 