```{=latex}
\clearpage
```
# Análisis funcional

\vspace{2.5cm}

*Las no linealidades de un sistema no deben considerarse como el
"demonio" por los ingenieros de control; de hecho, deben ser introducidas
durante el diseño del sistema de control, intencionalmente, a fin de alcanzar el objetivo.*
[@jairath]


\begin{figure}[H]
\centering
\includegraphics[width=0.63\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/pendulum.png}
\end{figure}

\newpage
## La Integral 



\newpage

## Funciones vistas como vectores

Las funciones pueden ser vistas, desde el punto de vista cualitativo,  
como *otro tipo* de vectores. Observe que las funciones se pueden sumar
para generar otra función. Tambien se pueden *escalar*: $\xi \cdot f(x)$

Observe y reflexione sobre la siguiente analogía:

```{=latex}
\[
\begin{aligned}
L(\vec{v}+ \xi \vec{w}) &= L(\vec{v}) + \xi L(\vec{w}) \\
\frac{d}{dx}(e^x+ \xi x^2) &= \frac{d}{dx}(e^x) + \xi \frac{d}{dx}(x^2)
\end{aligned}
\]
```

Entonces, mediante la comprobación de las propiedades de la lista
\ref{eq:props_espacios_vectoriales}, podemos afirmar que
el conjunto de todas las funciones reales 
$f: \mathbb R \rightarrow \mathbb R$ 
es un espacio vectorial sobre $\mathbb R$ pero no tiene una base en el sentido habitual  que se pueda escribir explícitamente, 


### Base del espacio de funciones reales

Aquí hay que distinguir según el tipo de base:

#### Base de Hamel (algebraica)

Existe por el axioma de elección (todo espacio vectorial tiene una base de Hamel) pero es una base enormemente infinita. No se puede escribir explícitamente. Además, no es numerable.

#### Base de Schauder (topológica, para espacios de Banach/Hilbert)

El espacio $\mathbb R^{\mathbb R}$ con la topología producto o puntual no es un espacio de Banach ni de Hilbert \footnote{Banach, Hilbert se explican más adelante.} con una norma razonable.

Ejemplos de subespacios que sí tienen base:

* Funciones continuas $C([a,b])$: tiene bases como la de polinomios (Weierstrass) o bases trigonométricas (Fourier).

* Funciones integrables $L^2(\mathbb R)$: tiene bases ortonormales como las de Haar o wavelets.

* Funciones polinómicas: base ${1, x, x^2 ,x^3, \dots }$

Pero para todas las funciones reales (sin restricciones de continuidad, integrabilidad, etc.), no hay una base de Schauder porque ni siquiera es un espacio métrico completo con una norma que permita series convergentes.

\vspace{1cm}
***Conclusión***

El espacio de funciones reales $\mathbb{R}^{\mathbb{R}}$ tiene base de Hamel, 
y su dimensión es:

```{=latex}
\[
\dim_{\mathbb{R}}(\mathbb{R}^{\mathbb{R}}) = 2^{\mathfrak{c}} = 2^{2^{\aleph_0}}.
\]
```
Dicha base existe por el axioma de elección, pero no se puede exhibir explícitamente.


***¿Se puede especificar una base concreta?***  No, salvo ciertos subespacios (como polinomios, continuas, etc.).

\newpage

Tabla comparativa de conceptos provenientes del algebra lineal


| Algebra lineal | Nombres alternativos
| ------------   | ------------- 
| Transformaciones lineales   | Operadores lineales
| Producto punto    | Producto interno
| Eigenvector   | Eigenfunción


: Conceptos del algebra lineal aplicados a funciones

Las funciones también se pueden *transformar*. Por ejemplo, al derivar una función, se obtiene una función diferente. Observe la siguiente analogía:



### Eigenvector y Eigenfunción


## Distancia

Una distancia (o *métrica*) es una función $d: X \times X \rightarrow [0,\infty)$
 que cumple:

  * positividad ($d(x,y)\geq 0$)
  * simetría ($d(x,y)=d(y,x)$) y
  * desigualdad triangular ($d(x,z)\leq d(x,y)+d(y,z)$)

La distancia nos sirve para saber que tan separados estan dos puntos. 
Una métrica debe satisfacer:

```{=latex}
\[
d(x,y)=0 \iff x=y
\]
```


En un espacio métrico $(X,d)$ no hay un punto señalado como *el cero*. Es decir, una métrica no necesita distinguir ningún punto como origen, mide la separación entre puntos, pero no el "tamaño" de un vector.

Conclusión parcial: En una métrica, las distancias entre puntos no varían al cambiar el origen. La norma, en cambio, fija el origen: *La longitud de un vector es su distancia exclusivamente a ese punto cero.*


## Espacios vectoriales normados

Un espacio vectorial normado es un espacio vectorial $V$ al que se le ha definido una norma $\| \cdot \|$, 

```{=latex}
\[
(V,\| \cdot \|)
\]
```

Una ***norma*** es una función $\|\cdot\|:V\longrightarrow [0,\infty)$
que asigna a cada vector $x \in V$ un número real no negativo, interpretado como su longitud.


En un espacio vectorial normado, la norma de un vector es la distancia entre ese vector y el vector cero.

```{=latex}
\[
\| x \| = d(x,0)
\]
```

Una norma debe satisfacer las siguientes propiedades.

1. Positividad y definitud

```{=latex}
\[
\|x\|\geq 0
\]
```

```{=latex}

\[
\|x\|=0\iff x=0.
\]
```

2. Homogeneidad,  es decir, para todo escalar $\alpha$,

```{=latex}
\[
\|\alpha x\|=|\alpha|\,\|x\|.
\]
```

3. Desigualdad triangular
```{=latex}

\[
\|x+y\|\leq \|x\|+\|y\|.
\]
```




Ejemplo de espacio vectorial normado:

```{=latex}
\[
( \mathbb R^2,\| \cdot \|_2)
\]
```

## Conexión entre distancia y norma

Una norma permite construir una métrica mediante

```{=latex}
\[
d(x,y):=\| x−y \|
\]
```

Es decir, para calcular la distancia entre $x$ y $y$, se calcula primero el vector que va de $y$ hacia $x$ y despues se calcula la longitud de ese vector.

El mensaje central es este:

***distancia=separación entre dos puntos***

mientras que

***norma=distancia de un vector al cero***

## Ortogonalidad y ángulo entre vectores

Hasta ahora hemos utilizado la norma para hablar de la longitud de un vector y la métrica para hablar de la distancia entre dos puntos. Sin embargo, en un espacio vectorial podemos hacernos otra pregunta:
¿Cómo podemos describir la relación entre la dirección de dos vectores?


Por ejemplo, en $\mathbb R^2$ podemos tener dos vectores que tengan exactamente la misma longitud, pero que apunten en direcciones diferentes. La norma nos permite saber cuánto mide cada vector, pero no es suficiente para determinar cómo están orientados dos vectores entre sí.

Para describir esta relación necesitamos introducir la idea de ángulo.


En $\mathbb R^2$, dados dos vectores no nulos $x$ e $y$, podemos hablar del ángulo $\theta$ que forman entre ellos.

```{=latex}
\[
0\leq\theta\leq\pi.
\]
```

Cuando dos vectores forman un ángulo de $90^\circ$, decimos que son perpendiculares.

En el contexto de espacios vectoriales, utilizaremos el término: ***Dos vectores son ortogonales si son perpendiculares.***

Lo escribiremos como


```{=latex}
\[
x\perp y.
\]
```

Por ejemplo, en $\mathbb R^2$,

```{=latex}
\[
x=(1,0),\qquad y=(0,1)
\]
```

son ortogonales. Geométricamente no es dificil visualizarlo.  El problema que aparece ahora es: *Cómo podemos determinar algebraicamente si dos vectores son ortogonales?*

Para responder esta pregunta necesitamos una operación que relacione dos vectores y que nos proporcione información sobre el ángulo que forman.

Esta operación será el producto interno.


## Producto interno 

El producto interno es una operación que nos permite generalizar las nociones geométricas de:
***longitud, ángulo*** y ***ortogonalidad*** (perpendicularidad)
que conocemos en $\mathbb R^2$ y $\mathbb R^3$ 
a cualquier espacio vectorial.

Un *producto interno* sobre un espacio vectorial real $V$ es una ***función*** que toma dos vectores 
$u,v \in V$ y devuelve un número real, se denota como:


```{=latex}
\[
\langle u, v \rangle \text{ o } u \cdot v
\]
```
y satisface los siguientes axiomas :

1. Simetria (o conmutatividad)

```{=latex}
\[
\langle u, v \rangle = \langle v, u \rangle
\]
```

2. Linealidad en el primer argumento

Si sumamos dos vectores en el primer argumento, el producto interno se distribuye sobre la suma; además, podemos sacar los escalares fuera del producto interno.



Aditividad:

```{=latex}
\[
\langle u+v,w \rangle=\langle u,w\rangle+ \langle v,w \rangle
\]
```


Homogeneidad:

```{=latex}
\[
\langle \xi u,w \rangle = \xi \langle u,w \rangle
\]
```

O bien:

```{=latex}
\[
\langle \xi u+v,w \rangle =\xi\langle u,w\rangle+\langle v,w \rangle
\]
```

(Nota: por simetría, también es lineal en el segundo argumento).


\newpage

3. Definido positivo 


* No negatividad:


```{=latex}
\[
\langle u,u\rangle \geq 0
\]
```

* Definición positiva estricta:

```{=latex}
\[
\langle u,u\rangle = 0 \iff u=0
\]
```

$u \cdot u$ nunca es negativo y solamente puede ser cero cuando $u$ es el vector cero.

### Longitud

8484: asdf

### Angulo 

8484: asdf

### Ortogonalidad

8484: asdf

---

:8484 trabaja esta parte a lo mas minimo posible..



La importancia del producto interno está en que contiene información geométrica sobre los vectores. En particular, el producto interno está relacionado con el ángulo $\theta$ entre dos vectores mediante

```{=latex}
\[
\langle x,y\rangle
=
\|x\|\,\|y\|\cos\theta.
\]
```



---
Recapitulando. un producto interno es una operación que toma dos vectores y produce un escalar:

```{=latex}
\[
\langle\cdot,\cdot\rangle:V\times V\longrightarrow\mathbb{F},
\]
```        

donde $\mathbb F$ es $\mathbb R$ o $\mathbb C$

En el caso real, el producto interno satisface, entre otras propiedades:

* linealidad,
* simetría,
* positividad.

El producto interno permite definir una norma:

```{=latex}

\[
\boxed{
\|x\|=\sqrt{\langle x,x\rangle}
}
\]
```
**Para generalizar: no se va a demostrar que el producto interno *genera* el ángulo, sino que se define el ángulo a través del producto interno.**

en R2 el producto interno revela el ángulo.

Pero en un espacio vectorial abstracto de dimensión infinita (ej. espacio de funciones continuas), no existe un "ángulo" dibujable ni una "ley de cosenos" preexistente.


La solución: 


1. Definir el producto interno $\langle \cdot, \cdot\rangle$ como una operación que cumple simetría, linealidad y positividad.

2. Definir la norma inducida: 

```{=latex}

\[
\|v\|=\sqrt{\langle v,v\rangle}
\]
```
3. Probar la Desigualdad de Cauchy-Schwarz:

```{=latex}

\[
| \langle v,v\rangle | \leq \|u\| \|v\|
\]
```

4. Como consecuencia, el número 

```{=latex}
\[
\frac{| \langle v,v\rangle |}{\|u\| \|v\|}
\]
```
siempre está entre $-1$ y $1$

5. Entonces se define el ángulo $\theta$ entre dos vectores no nulos mediante la fórmula:

8484: mejorar parentesis y R2 abaojo

```{=latex}
\[
\theta = arccos(\frac{| \langle v,v\rangle |}{\|u\| \|v\|})
\]
```

y por definición, $\theta \in [0,\pi]$

¿Qué hacen con esto? No están "descubriendo" un ángulo que ya existía. Están extendiendo el concepto de ángulo desde R2R2 hacia cualquier espacio abstracto, garantizando que en R2R2 esta nueva definición coincida exactamente con el ángulo euclidiano que ya conoces.


### Demostracion $\langle u,0\rangle$


Como desarrollar la siguiente demostracion de que:

```{=latex}
\[
\langle u,0\rangle
\]
```

Partimos de que:

$0+0=0$

Entonces podemos escribir:


```{=lngleatex}
\[
\langle u,0\rangle = \langle u,0+0\rangle
\]
```


## Norma de una función

En $\mathbb R^2$, estamos acostumbrados a interpretar la *norma* como una *longitud*. En espacios de funciones, la interpretación geométrica de *longitud* puede dejar de ser tan directa, pero seguimos utilizando una *norma* para medir el tamaño de una función. La ***norma*** es, entonces, una forma general de medir el tamaño de un vector.

Dos posibilidades diferentes de *norma de función* serían:

```{=latex}
\[
\|f\|_\infty = \sup_x |f(x)|
\]
```

```{=latex}
\[
\|f\|_2 = \sqrt{\int |f(x)|^2\,dx}
\]
```

### Norma 1 de un vector

```{=latex}
\[
\|e\|_1
=
\int_0^\infty |e(t)|\,dt
\]
```

8484: La norma 1 puede representar el error acumulado
a lo largo del tiempo.

### Norma 1 de una función 

asdf

### Norma 2 de un vector

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



### Norma $\infty$

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


\newpage
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

