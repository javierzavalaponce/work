### root locus. 3er orden

**Ejemplo:** Construir LGR 

```{=latex}
\begin{equation}
\begin{aligned}
G(s) = \frac{s+5}{(s-1)(s+2)(s+3)(s+4)}
\end{aligned}
\end{equation}
```

#### PIA (Punto de Intersección de las Asintotas)

\
* Número de polos: $n$=4 (en $s= +1, −2, −3, −4$)
\
* Número de ceros: $m$=1 (en s=−5s=−5)
\
* Diferencia: n−m → tres asíntotas

El centroide o P.I.A. es:

```{=latex}
\begin{equation}
\begin{aligned}
P.I.A = \frac{\sum \text{polos} - \sum \text{ceros}}{n - m}
\end{aligned}
\end{equation}
```

```{=latex}
\begin{equation}
\begin{aligned}
P.I.A = \frac{(+1-2-3-4)-(-5)}{4 - 1} = \frac{-3}{3} = -1
\end{aligned}
\end{equation}
```

#### Resumen de las reglas del LGR

Comprender las reglas del LGR permite visualizar el efecto de
añadir o quitar un polo o un cero al sistema sin realizar calculos matematicos.

0. asdf

1. El número de ramas del root locus es igual al número de polos del sistema en lazo abierto $n$.

2. El root locus es simétrico *respecto al eje real*.

3. Un punto del eje real pertenece al LGR si el número de *polos y ceros* reales a su derecha es impar.

4. Puntos de inicio y fin ($k = 0$ y $k$ = $\infty$):

    Cuando la ganancia $k$ = 0, las ramas inician en los polos.

    Cuando la ganancia $k$ $\rightarrow$ $\infty$ , las ramas terminan en los ceros (si los hay) o se van al infinito siguiendo las asíntotas. (Los rayos de la rueda son el camino que siguen las ramas que no llegan a un cero).

\begin{figure}[H]
\centering
\includegraphics[height=0.35\textheight]{./img/rlocus_matlab_style.png}
\caption{root locus del RC}
\end{figure}


Versión completa mental del LGR

Si lo quieres ver limpio, el “esqueleto completo” es:

Polos → inicio
Ceros → final
Eje real → regla de impares
Asíntotas → comportamiento al infinito
Centroide → punto de salida de asíntotas
Condición de ángulo → pertenencia
Condición de magnitud → ganancia
Breakpoints → cambios de dirección
Cruce imaginario → estabilidad



\newpage
 