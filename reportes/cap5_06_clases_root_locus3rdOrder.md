### root locus. 3er orden

**Ejemplo:** Construir LGR 

```{=latex}
\begin{equation}
\begin{aligned}
G(s) = \frac{s+5}{(s-1)(s+2)(s+3)(s+4)}
\end{aligned}
\end{equation}
```

Primero, ubicar los polos y ceros:
Polos: $1,−2,−3,−4$
Cero:  $−5$

* Número de polos: $n$=4 (en $s= +1, −2, −3, −4$)

* Número de ceros: $m$=1 (en $s=−5$)

* Número de asíntotas $n−m$  ($4-1=3$ en este caso)

* Número de trayectorias $n$  (núm. de polos)

* El centroide o **P.I.A.** (Punto de Intersección de las Asintotas) es:

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

* Hay $n$ = 4 trayectorias: Una termina en el cero $s=−5$
y las otras tres se van al infinito mediante asíntotas.

* El tramo (entre $s=1$ y $s=-2$) sí es es parte del LGR. Estas trayectorias
interactúan entre sí produciendo un punto de ruptura *breakaway* hacia el plano complejo.

* El tramo (entre $s=-3$ y $s=-4$) sí es es parte del LGR. Estas trayectorias
interactúan entre sí.

    * Una rama inicia en el polo $s=−4$ y se desplaza sobre el eje real hacia el cero $s=−5$ . Los ceros *atraen* trayectorias del LGR. (**REVISAR ESTE PUNTO**)

    * Otra rama inicia en el polo s=−3 y eventualmente se dirige hacia infinito.


\begin{figure}[H]
\centering
\includegraphics[height=0.4\textheight]{./img/rlocus_with_asymptotes.png}
\caption{LGR con asíntotas (líneas punteadas) y $n=3$ trayectorias}
\end{figure}







\newpage

#### Resumen de las reglas del LGR

\

1. Un punto del eje real *pertenece* al LGR si el número de *polos y ceros* reales a su derecha es *impar*.

2. *Asíntota* y *trayectoria* son dos cosas diferentes, pero a veces se superponen.
El número de asíntotas ($n - m$) del LGR es igual a la diferencia entre el número de polos ($n$) y el número de ceros($m$)  del sistema en lazo abierto:
    * Número de **asíntotas** = $n - m$ (si $n$ > $m$)
    * Número de **trayectorias** = $n$ (número de polos)


3. Cada trayectoria del LGR comienza en un polo ($k=0$) y termina en un cero. 
    * Polos $\rightarrow$ inicio
    * Ceros $\rightarrow$ final
    * Si no hay suficientes polos o ceros para hacer pares, entonces las trayectorias van o vienen a  $\rightarrow \infty$


4. El LGR es simétrico *respecto al eje real*. (Las raíces complejas siempre aparecen en pares conjugados). El LGR es espejo en el eje real.


5. Las **asíntotas** son *rayos* (líneas rectas punteadas) que parten del P.I.A. con ángulos fijos y equiespaciados (máxima separación angular posible). Guían las trayectorias del LGR que no terminan en ceros finitos, como "rieles" hacia el infinito cuando $k$ es muy grande. 
    * Los angulos de las asíntotas 

 

\newpage
 