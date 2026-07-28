```{=latex}
\clearpage
```
# Espacio Métrico


Un espacio métrico es un par

```{=latex}
\[
(X,d)
\]
```

 donde $X$ es un *conjunto* y $d$ es una ***función distancia*** que cumple cuatro axiomas fundamentales [@kreyszig] :

* $d$ es real, no negativa y finita
* la distancia es cero si y solo si los puntos son iguales $d(x,y)=0$ si $x=y$
* es simétrica, $d(x,y)$ = $d(y,x)$
* cumple la desigualdad triangular (la distancia directa es menor o igual que la suma de distancias indirectas): $d(x,y) \leq d(x,z)+d(y,z)$

\vspace{1.5cm}

**Ejemplo 1**

\vspace{1cm}

* Con $X$ como la recta real $\mathbb{R}$ 

```{=latex}
\[
d(x, y) = |x - y|
\]
```

\vspace{1cm}

**Ejemplo 2**

Con $X$ como el plano $\mathbb{R}^2$, también llamado plano euclidiano, si $a=(x_1,y_1)$ y $b=(x_2,y_2)$ son dos puntos en el plano. Se pueden definir dos métricas : $d_1$ y $d_2$. En este caso se obtienen los espacios métricos $(\mathbb{R}^2,d_1)$ y $(\mathbb{R}^2,d_2)$

```{=latex}
\[
\begin{aligned}
 d_1(a, b) &= \sqrt{(x_2-x_1)^2 + (y_2-y_1)^2} \\
 d_2(a, b) &= |x_2-x_1| + |y_2-y_1|
\end{aligned}
\]
```

\newpage

**Ejemplo 3**

Con $X$ como el conjunto de todas las sucesiones acotadas de números complejos, se forma el espacio de sucesiones denotado por $l^\infty$. Cada elemento de $X$ es una sucesión compleja. Tomemos por ejemplo, los elementos $x, y \in X$:

```{=latex}
\[
x = (\xi_1,\xi_2,\ldots) \quad \text{o} \quad x = (\xi_j)
\]
```

```{=latex}
\[
y = (\eta_1,\eta_2,\ldots) \quad \text{o} \quad y = (\eta_j)
\]
```


La regla para medir qué tan lejos están dos sucesiones (dos *"puntos"*) de $X$ entre sí:

```{=latex}
\[
 d(x, y) = sup_{j \in \mathbb{N}} |\xi_j - n_j|
\]
```

$sup$ significa el supremo, que  es simplemente el valor más grande de
(o el valor al que se acercan) las diferencias.

\newpage

## Conjunto Abierto, Conjunto Cerrado y Vecindad

Son conceptos *inspirados* en la geometría que juegan un rol importante en conexión con los espacios métricos.

* Bola abierta: Dado un punto $x_0 \in X$ y un número real $r > 0$, se define como el conjunto de todos los puntos $x \in X$ cuya distancia a $x_0$ es estrictamente menor que $r$.

```{=latex}
\[
B(x_0,r)=\{ x \in X \mid d(x, x_0) < r \}
\]
```

* Bola cerrada: Es el conjunto de todos los puntos $x \in X$ cuya  distancia a $x_0$ es menor o igual que $r$.

```{=latex}
\[
\overline B(x_0,r)=\{ x \in X \mid d(x, x_0) \leq r \}
\]
```

* Esfera: Es el conjunto de todos los puntos $x \in X$ cuya distancia a $x_0$ es exactamente igual a $r$.

```{=latex}
\[
S(x0,r)=\{ x \in X \mid d(x, x0) = r \}
\]
```

\vspace{1cm}

Se cumple que: 

```{=latex}
\[
\overline B(x_0,r) = B(x_0,r) \cup S(x_0,r)
\]
```

Las bolas abiertas, bolas cerradas y esferas son conjuntos definidos directamente a partir de la distancia. Sin embargo, su verdadera importancia radica en que permiten caracterizar la estructura topológica de un espacio métrico.


### Conjunto Abierto

Un conjunto $A \subseteq X$ se dice abierto si para todo punto $x \in A$ existe una bola abierta completamente contenida en $A$

```{=latex}
\[
\forall x\in A,\;
\exists r>0
\text{ tal que }
B(x,r)\subseteq A.
\]
```

En otras palabras, ningún punto de un conjunto abierto se encuentra $"pegado"$ a su frontera; alrededor de cada punto siempre es posible dibujar una pequeña bola abierta que permanece completamente dentro del conjunto. La bola abierta constituye, por tanto, el modelo básico de un conjunto abierto.


### Conjunto Cerrado

Un conjunto $F \subseteq X$ se dice cerrado cuando contiene todos sus puntos límite. Un conjunto F es cerrado si y sólo si todo lo que queda fuera de $F$ forma un conjunto abierto:

```{=latex}
\[
F
\text{ es cerrado }
\Longleftrightarrow
X\setminus F
\text{ es abierto.}
\]
```

**Ejemplo en la recta real**

Consideremos, por ejemplo, el intervalo $F=[0,1]$. Este es un conjunto cerrado. Su complemento en $\mathbb{R}$ está formado por todos los números reales menores que 0 y mayores que 1; es decir:

```{=latex}
\[
\mathbb{R} \setminus F = (-\infty,0) \cup (1,\infty)
\]
```


Aunque su nombre pueda sugerirlo, un conjunto cerrado no se define mediante bolas cerradas. La bola cerrada es simplemente un ejemplo frecuente de conjunto cerrado en muchos espacios métricos, pero la definición fundamental proviene de la noción de conjunto abierto.




### Vecindad

Una vecindad de un punto x$_0$ es cualquier conjunto que contiene una bola abierta centrada en dicho punto.

```{=latex}
\[
V
\text{ es vecindad de }
x_0
\Longleftrightarrow
\exists r>0
\text{ tal que }
B(x_0,r)\subseteq V.
\]
```

Es decir, una vecindad puede tener prácticamente cualquier forma, siempre que incluya una pequeña bola abierta alrededor del punto considerado. La bola abierta es, por tanto, la vecindad más simple y fundamental.


