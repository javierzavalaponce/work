```{=latex}
\clearpage
```
# Análisis funcional

## Espacios vectoriales normados

Un espacio vectorial normado es un espacio vectorial $V$ al que se le ha definido una norma $\| \cdot \|$, de modo que podemos hablar del “tamaño” o “longitud” de sus elementos:

```{=latex}
\[
(V,\| \cdot \|)
\]
```

Por ejemplo:

```{=latex}
\[
( \mathbb R^2,\| \cdot \|_2)
\]
```
es un espacio vectorial normado.

## Norma 2

La norma 2, también llamada norma euclídea, es una forma particular de medir el tamaño de un vector. En $\mathbb R^n$, se define como

```{=latex}
\[
\|v\|_2
=
\sqrt{
|v_1|^2+|v_2|^2+\cdots+|v_n|^2
}.
\]
```

Si el vector tiene componentes reales, podemos escribir simplemente:
```{=latex}
\[
\|v\|_2
=
\sqrt{
v_1^2+v_2^2+\cdots+v_n^2
}.
\]
```

Por ejemplo, para el vector $v=(3,4)$, $\|v\|_2 = \sqrt{3^2+4^2} = 5$

\newpage	 

### Norma 2 de una función

La misma idea puede extenderse a espacios de funciones. En lugar de sumar los cuadrados de las componentes de un vector, integramos el cuadrado del valor absoluto de la función.

Para una función $f$ definida en un intervalo $[a,b]$, definimos:

```{=latex}
\[
\boxed{
\|f\|_2
=
\sqrt{
\int_a^b |f(x)|^2\,dx
}
}
\]
```

Siempre que la integral sea finita. Por ejemplo , si:

```{=latex}
\[
f(x)=x,
\qquad x\in[0,1],
\]
```

```{=latex}
\[
\|f\|_2
=
\sqrt{
\int_0^1 x^2\,dx
}
=
\sqrt{\frac{1}{3}}
=
\frac{1}{\sqrt{3}}.
\]
```

La analogía puede verse así:

```{=latex}
\[
\begin{aligned}
\text{Vector:}\qquad
\|v\|_2
&=
\sqrt{\sum_{i=1}^n |v_i|^2}
\\[8pt]
\text{Función:}\qquad
\|f\|_2
&=
\sqrt{\int_a^b |f(x)|^2\,dx}.
\end{aligned}
\]
```

## Norma 1

```{=latex}
\[
\|e\|_1
=
\int_0^\infty |e(t)|\,dt
\]
```

8484: La norma 1 puede representar el error acumulado
a lo largo del tiempo.

## Norma $\infty$

```{=latex}
\[
\|e\|_\infty = \sup_x |f(x)|
\]
```

8484: La norma infinito puede representar: *¿Cuál fue el peor error que cometió el sistema?*



## Convergencia 

Una vez que tenemos una norma, podemos utilizarla para medir la distancia entre dos elementos de un espacio. Si $u,v\in V$, definimos la distancia entre ellos como:

```{=latex}
\[
d(u,v)=\|u-v\|.
\]
```

Por lo tanto, la norma no solamente nos permite hablar del tamaño de un vector. También nos permite decir qué tan cerca están dos elementos entre sí.

Consideremos una sucesión de elementos de un espacio vectorial normado:

```{=latex}
\[ v_1,v_2,v_3,\ldots \]
```



Decimos que esta sucesión converge a un elemento $v\in V$ si, a medida que avanzamos en la sucesión, los elementos se acercan cada vez más a $v$, es decir que a medida que el índice $n$ tiende a 
$\infty$, los elementos $v_n$ aproximan a $v$ de manera arbitraria.

La definición mediante la norma es:

```{=latex}
\[ 
v_n\longrightarrow v \quad\Longleftrightarrow\quad \|v_n-v\|\longrightarrow0
\]
```

Es decir, la distancia entre $v_n$ y $v$ tiende a cero. Por ejemplo, en $\mathbb R$ consideremos:

```{=latex}
\[ 
v_n=\frac{1}{n}
\]
```


Entonces:
```{=latex}
\[
\lim_{n\rightarrow\infty}\frac{1}{n}=0.
\]
```

Podemos expresar esto utilizando la norma habitual de $\mathbb R$ (valor absoluto):

```{=latex}
\[
\left\|v_n-0\right\|
=
\left|\frac{1}{n}\right|
\longrightarrow0.
\]
```

Por lo tanto:
```{=latex}
\[ v_n\longrightarrow0. \]
```
Es decir, la flecha es la notación que resume todo ese proceso de acercamiento. y se lee como:
la sucesión $v_n$ tiende a cero.

### Convergencia de funciones

Supongamos que tenemos una sucesión de funciones
```{=latex}
\[
f_1,f_2,f_3,\ldots
\]
```
y queremos saber si se aproxima a una función $f$.
La respuesta depende de la norma que hayamos elegido. Por ejemplo, utilizando la norma $2$:

```{=latex}
\[
\|f_n-f\|_2
=
\sqrt{
\int_a^b |f_n(x)-f(x)|^2\,dx
}.
\]
```

Decimos que $f_n$ converge a $f$ en la norma $2$ si:

```{=latex}
\[
\boxed{
\|f_n-f\|_2\longrightarrow0.
}
\]
```

Esto significa que el "error" entre $f_n$ y $f$, medido mediante la norma $2$, se hace cada vez más pequeño.

En cambio, si utilizamos la norma infinito:

```{=latex}
\[
\|f_n-f\|_\infty
=
\sup_x|f_n(x)-f(x)|,
\]
```
la convergencia significa:

```{=latex}
\[
\boxed{
\|f_n-f\|_\infty\longrightarrow0.
}
\]
```

Por lo tanto, una misma sucesión de funciones puede converger según una norma y no converger según otra. Esto es importante porque ***la noción de convergencia depende de la norma que hayamos elegido.***

## Completitud

### Sucesiones de Cauchy

Para hablar de completitud necesitamos introducir primero el concepto de sucesión de Cauchy.

Una sucesión $(v_n)$ es de Cauchy si sus elementos se acercan entre sí cada vez más.

Formalmente:
```{=latex}
\[
\boxed{
\forall\varepsilon>0,\;
\exists N\in\mathbb N
\text{ tal que si }m,n>N,
\quad
\|v_n-v_m\|<\varepsilon.
}
\]
```

La idea es que, a partir de cierto punto, podemos hacer que la distancia entre cualesquiera dos elementos de la sucesión sea tan pequeña como queramos.

Una sucesión convergente siempre es de Cauchy.

Es decir:
```{=latex}
\[
v_n\longrightarrow v
\quad\Longrightarrow\quad
(v_n)\text{ es de Cauchy}.
\]
```
 
 Si una sucesión es de Cauchy, ¿necesariamente converge a un elemento que pertenece al espacio?
La respuesta no siempre es sí.

Un espacio vectorial normado es ***completo*** si toda sucesión de Cauchy de elementos del espacio converge a un elemento que también pertenece al espacio.

Formalmente: ***Toda sucesión de Cauchy en $V$ converge a algún $v\in V$.***


## Espacio de Banach

Un espacio vectorial normado *completo* recibe el nombre de espacio de Banach. La completitud evita que una sucesión de elementos de nuestro espacio *"escape"* hacia un objeto que ya no pertenece al espacio.

Podemos pensar en una sucesión:

```{=latex}
\[
v_1,v_2,v_3,\ldots
\]
```

que se va acercando cada vez más a algo. Si el espacio es completo, podemos estar seguros de que ese límite también pertenece al espacio.


```{=latex}
\[
\text{sucesión de elementos de }V
\quad\xrightarrow{\text{Cauchy}}\quad
\text{límite en }V
\]
```

Esto resulta especialmente importante en análisis funcional porque muchas construcciones se realizan mediante aproximaciones sucesivas.


Por ejemplo, en el estudio de sistemas dinámicos y de control podemos aproximar una señal, una trayectoria o una solución mediante una sucesión de funciones:

```{=latex}
\[
f_1,\;f_2,\;f_3,\ldots
\]
```

Si demostramos que la sucesión es de Cauchy respecto de una determinada norma y el espacio es completo, entonces sabemos que existe una función límite dentro del espacio.


**Los 3 ingredientes obligatorios para un espacio de Banach:**


1. Ser un espacio vectorial.

2. Tener una *Norma*.

* Ser *Completo*. El objeto límite al que tienden tiene que estar dentro del espacio. 

### Analogia para afianzar el concepto

Imagine que trabaja con la suseción de números racionales:

```{=latex}
1, 1.4, 1.41, 1.414, 1.4142,... 
```

Esos números se acercan cada vez más entre sí, pero el límite ($\sqrt 2$) no es un número racional,
Por eso, los racionales no son un espacio de Banach.
En cambio, los números reales sí lo son: cualquier sucesión que se aproxime tiene su límite dentro de los reales. Son un espacio sin fugas.


## Hilbert

8484: Si tenemos producto interno y el espacio es completo, se llama Hilbert
. Aquí caen las series de Fourier y las bases ortonormales. Sección 1.5 de [@hstark]


## Operadores

8484: Funciones que van de un espacio a otro (operadores). Se define continuidad (que en espacios normados es lo mismo que estar acotado) y el espacio dual (funcionales lineales). 
Capítulo 2 del [@kreyszig] 

