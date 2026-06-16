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
Polos: $1,-2,-3,-4$
Cero:  $-5$

* Número de polos: $n$=4 (en $s= +1, -2, -3, -4$)

* Número de ceros: $m$=1 (en $s=-5$)

* Número de asíntotas $n-m$  ($4-1=3$ en este caso)

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

* Hay $n$ = 4 trayectorias: Una termina en el cero $s=-5$
y las otras tres se van al infinito mediante asíntotas.

* El tramo (entre $s=1$ y $s=-2$) sí es es parte del LGR. Estas trayectorias
interactúan entre sí produciendo un punto de ruptura *breakaway* hacia el plano complejo.

* El tramo (entre $s=-3$ y $s=-4$) sí es es parte del LGR. Estas trayectorias
interactúan entre sí.

    * Una rama inicia en el polo $s=-4$ y se desplaza sobre el eje real hacia el cero $s=-5$ . Los ceros *atraen* trayectorias del LGR. (**REVISAR ESTE PUNTO**)

    * Otra rama inicia en el polo s=-3 y eventualmente se dirige hacia infinito.


\begin{figure}[H]
\centering
\includegraphics[height=0.4\textheight]{../img/rlocus_with_asymptotes.png}
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
#### "Método del dibujante" (4 pasos para memorizar las reglas del LGR)

\


**Paso 0**: (Antes de empezar): Escribe G(s) en su forma factorizada: 

```{=latex}
\[
\frac{s-ceros}{s-polos}
\]
```

Marca los polos con una X y los ceros con un O en el plano complejo.

**Paso 1**: El esqueleto (la estructura gruesa)

* Regla 1: ¿Cuántas ramas? = Número de polos (X's).

* Regla 2: ¿Hacia dónde van al final? Las ramas que sobran van al infinito (tantas como polos - ceros).

* Regla 3: ¿En qué dirección van al infinito? Las asíntotas. Sus ángulos se calculan con la fórmula: 

```{=latex}
\[
angulos = \frac{(2q+1)·180^\circ}{n - m}
\]
```

* $q$ = 0, 1, 2, ..., (n - m - 1)

* $n$ = número de polos del sistema en lazo abierto

* $m$ = número de ceros del sistema en lazo abierto


***Ejemplo práctico***

Con $n = 4$ polos y $m = 1$ cero. Entonces:

$n - m = 3$ (tres asíntotas)

$q = 0, 1, 2$

Calculamos:

$q = 0: (2·0 + 1)·180^\circ / 3 = 180^\circ/3 = 60^\circ$
$q = 1: (2·1 + 1)·180^\circ / 3 = 3·180^\circ/3 = 180^\circ$
$q = 2: (2·2 + 1)·180^\circ / 3 = 5·180^\circ/3 = 300^\circ$

Las tres asíntotas salen a $60^\circ$, $180^\circ$ y $300^\circ$.


Sus centros se calculan con la fórmula de centroides.

(Con esto ya tienes el andamiaje del dibujo)

**Paso 2**: El camino sobre la línea recta (el eje real)

* Regla 4: Recorre el eje real de derecha a izquierda. Donde haya un número IMPAR de X's y O's a tu derecha, pinta una línea gruesa. Esa zona pertenece al LGR.
(Con esto ya sabes por dónde van las ramas sobre el suelo)

**Paso 3**: Los "puntos de inflexión" (donde las ramas chocan)

* Regla 5: Calcula $dK/ds = 0$ (derivando $K = -1/G(s)$) y resuelve. 
Esos puntos son los puntos de ruptura 
$(breakaway/break-in)$. Dibújalos.

(Con esto ya sabes dónde las ramas se separan o se juntan)

**Paso 4**: Los "detalles finos" (cerca de los polos y ceros complejos)

* Regla 6: Si hay polos o ceros complejos, calcula el ángulo con el que salen o llegan usando la regla del argumento. (Esto es solo para darle precisión al dibujo en zonas complicadas; si no hay complejos, te saltas este paso)

**Paso 5** (Opcional): El "tope" con el eje imaginario

* Regla 7: Para saber si el sistema se vuelve inestable al subir K, calcula dónde cruza el eje imaginario (usando Routh-Hurwitz o haciendo $s = jω$).

El truco final para recordarlo siempre:  Asocia las reglas a los dedos de tu mano izquierda (es absurdo, pero funciona):

* Pulgar = Polos y ceros (marcar X y O).

* Índice = Asíntotas (hacia dónde van al infinito).

* Corazón = Eje real (lo que está a la derecha, cuenta impar).

* Anular = Puntos de ruptura (derivar K).

* Meñique = Ángulos de salida (solo si h

Cuando te enfrentes a un problema, recorre tus dedos en ese orden y las 8 reglas saldrán solas, porque las dos últimas (cruce con eje imaginario y simetría) son tan obvias que no hace ni falta memorizarlas 
(la simetría la ves a ojo, y el cruce lo sacas de Routh).

*La moraleja:* No memorices las reglas como si fueran conjuros mágicos. Todas son hijas de la ecuación 


```{=latex}
\[
1 + K·G(s)=0. 
\]
```

Si algún día olvidas una regla, vuelve a la condición de ángulo de 180° y dedúcela sobre la marcha con un dibujo rápido. Un ingeniero no es el que más memoria tiene, sino el que entiende el origen de las herramientas que usa.


\newpage


 