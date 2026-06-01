```{=latex}
\clearpage
```

# Simulación de Sistemas Dinámicos Usando *julia* 


## Sistemas dinámicos lineales LTI


### La convolución

https://www.youtube.com/watch?v=IaSGqQa5O-M


Un sistema lineal e invariante en el tiempo (LTI, Linear Time-Invariant) puede describirse mediante una relación entrada-salida basada en la operación de convolución:


\begin{equation}
\begin{aligned}
y(t)=\int_{0}^{t} g(t-\tau)u(\tau),d\tau
\end{aligned}
\end{equation}

donde $u(t)$ representa la señal de entrada, $y(t)$ la salida del sistema y $g(t)$ la respuesta al impulso.

La expresión anterior indica que la salida del sistema en un instante $(t)$ depende no solamente del valor actual de la entrada, sino también de los valores pasados de dicha señal. En este sentido, un sistema dinámico puede interpretarse como un sistema con memoria.

La función $g(t)$, conocida como respuesta al impulso, describe cómo responde el sistema ante una excitación instantánea ideal. Una propiedad fundamental de los sistemas LTI es que cualquier señal de entrada puede entenderse como una superposición continua de impulsos desplazados en el tiempo. Debido a la linealidad, el sistema responde a cada uno de estos impulsos de manera independiente; y debido a la invariancia temporal, todas las respuestas poseen la misma forma, cambiando únicamente su desplazamiento temporal.

La operación de convolución representa entonces la suma continua de todas esas respuestas elementales ponderadas por la entrada (u(t)). En otras palabras, la salida del sistema surge de acumular la influencia de entradas pasadas sobre el comportamiento presente.

Esta propiedad permite describir una gran variedad de sistemas físicos mediante una única función $g(t)$, simplificando notablemente su análisis y simulación.




















