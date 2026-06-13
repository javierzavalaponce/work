```{=latex}
\clearpage
```

# Solución númerica de ecuaciones diferenciales

## Método de Euler.

Euler desarrolló estas ideas durante el siglo XVIII, a partir de una ecuación diferencial como:


```{=latex}
\[
\dot{x} = f(x,t)
\]
```


se aproxima la evolución usando pequeños pasos de tiempo:

\begin{equation}
\begin{aligned}
\frac{x_{k+1}-x_k}{\Delta t}   =  f(x,t)
\end{aligned}
\label{eq:definicion_euler}
\end{equation}

Esta expresión se utilizará mas adelante (Ver figuras 
\ref{fig:integrador_bloques} y 
\ref{fig:grafica_resultado00}
)





