```{=latex}
\clearpage
```

## El bloque de retardo


Un sistema con retardo puro reproduce la señal de entrada después de un intervalo de tiempo $T$. Su salida está dada por:

$$
y(t)=x(t-T)
$$

donde $T>0$ representa el tiempo de retardo.
Numéricamente un retardo es esencialmente un buffer (una cola o memoria).

Para un sistema lineal e invariante en el tiempo, con condiciones iniciales nulas, la transformada de Laplace permite expresar esta relación como $Y(s)=e^{-sT}X(s)$.

Un retardo puro de $T$ segundos tiene función de transferencia
$$
H(s)=e^{-sT}.
$$
Evaluada en $s=j\omega$, su respuesta en frecuencia es
$$
H(j\omega)=e^{-j\omega T}.
$$
Su \textbf{magnitud} es constante:
$$
|H(j\omega)|=|e^{-j\omega T}|=1 \quad\text{para toda }\omega,
$$
es decir, el retardo \textbf{no amplifica ni atenúa} ninguna frecuencia.
Su \textbf{fase}, en cambio, depende de la frecuencia:
$$
\angle H(j\omega)=-\omega T.
$$
La razón es que retrasar una senoide $\sin(\omega t)$ en $T$ segundos
la convierte en $\sin(\omega(t-T))=\sin(\omega t-\omega T)$: el argumento
cambia en $-\omega T$, y ese cambio \textbf{es} el desfase.

La función $e^{-sT}$ \textbf{no es una función racional} de $s$
(no es un cociente de polinomios: es una serie infinita), por lo que
no puede representarse exactamente mediante una función de transferencia
racional de orden finito. En consecuencia, un retardo puro no tiene
polos finitos en el sentido habitual. Al incluirlo en un lazo cerrado,
por ejemplo
$$
1+K e^{-sT}=0,
$$
aparecen \textbf{infinitos polos} alineados en la recta vertical
$$
\sigma=\frac{1}{T}\ln K,
$$
espaciados verticalmente cada $2\pi/T$. Su estabilidad depende de $K$:
\begin{itemize}
  \item $K>1$: todos los polos tienen $\sigma>0$ $\Rightarrow$ \textbf{todos inestables};
  \item $K=1$: todos sobre el eje imaginario $\Rightarrow$ \textbf{marginal};
  \item $K<1$: todos con $\sigma<0$ $\Rightarrow$ \textbf{todos estables}.
\end{itemize}

\newpage

Cuando pasamos al dominio discreto, el retardo se implementa mediante un *buffer circular* de $N$ muestras. 

\begin{figure}[H]
\centering
\includegraphics[width=0.67\textwidth,trim=0cm 10cm 0cm 10cm,clip]{../img/diag_retardo_sin_retroalim.pdf}
\caption{Retardo puro en discreto. Contraparte de $y(t)=x(t-T)$, buffer $N=4$}
\label{fig:delay0}
\end{figure}

Si $y[n]=x[n-N]$, entonces:

$$
Y(z)=z^{-N}X(z)
$$

Función de transferencia del retardo puro en discreto:

$$
\boxed{H(z)=z^{-N}}
$$


\newpage 

## Sistema discreto en lazo cerrado con retardo de $N$ muestras y ganancia de realimentación $g$

(Delay con realimentación / Feedback Delay)

Al sumar la señal de entrada $x[n]$ con una copia retardada y escalada por una ganancia $g$.
Definiendo a $d[n]$ como la salida del bloque de retardo (el buffer):

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 12cm 0cm 8cm,clip]{../img/diag_retardo_prg.pdf}
\caption{Diagrama delay con \(g \in [0,1]\) y buffer \(N=4\)}
\label{fig:delay000}
\end{figure}


$$
y[n]=x[n]+ d[n]
$$

$$
d[n]=x[n−N]+g \cdot d[n−N]
$$

Para obtener una ecuación en diferencias que dependa únicamente de la entrada y de la salida del sistema, 
sustituimos $d[n]$ y $d[n−N]$ en la primera ecuación. 
Sabemos que $d[n−N]=y[n−N]−x[n−N]$
Por lo tanto:

$$
y[n]=x[n]+(x[n−N]+g⋅(y[n−N]−x[n−N]))
$$

Agrupando términos:

$$
y[n]=x[n]+(1−g)x[n−N]+g⋅y[n−N]
$$

