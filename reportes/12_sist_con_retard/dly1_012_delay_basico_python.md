```{=latex}
\clearpage
```



## Retardo puro

Un sistema con retardo puro reproduce la señal de entrada después de un intervalo de tiempo $T$. Su salida está dada por:

$$
y(t)=x(t-T)
$$

donde $T>0$ representa el tiempo de retardo.

Para un sistema lineal e invariante en el tiempo, con condiciones iniciales nulas, la transformada de Laplace permite expresar esta relación como:

$$
Y(s)=e^{-sT}X(s)
$$

Por tanto, la función de transferencia del retardo puro es:

$$
\boxed{H(s)=\frac{Y(s)}{X(s)}=e^{-sT}}
$$

El retardo introduce una fase dependiente de la frecuencia, pero no modifica la magnitud de la respuesta en frecuencia:

$$
|H(j\omega)|=1
$$

$$
\angle H(j\omega)=-\omega T
$$

Es importante observar que $e^{-sT}$ no es una función racional de $s$. Por ello, un retardo puro no puede representarse exactamente mediante una función de transferencia racional de orden finito.


## Delay sin realimentación

Un delay sin realimentación suma la señal de entrada con una copia retardada y escalada:

$$
y[n]=x[n]+g,x[n-N]
$$

Aplicando la transformada Z:

$$
Y(z)=X(z)+g z^{-N}X(z)
$$

Factorizando la entrada:

$$
Y(z)=\left(1+g z^{-N}\right)X(z)
$$

La función de transferencia resulta:

$$
\boxed{H(z)=1+g z^{-N}}
$$
El sistema conserva la señal, pero la entrega más tarde. 

## Sistema digital con retardo

El delay es un sistema con memoria. 


\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 10cm 0cm 8cm,clip]{../img/diag_retardo_prg.pdf}
\caption{Diagrama delay con \(g \in [0,1]\) y buffer \(N=4\)}
\label{fig:delay000}
\end{figure}


Las ecuaciones en diferencias son:

Salida:
$$
y_n=x_n+d_n
$$
Delay:
$$
d_n=x_{n−N}+ g \cdot d_{n−N}
$$

El buffer circular es la implementación eficiente de $x_{n−N}$. 


