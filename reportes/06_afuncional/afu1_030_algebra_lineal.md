```{=latex}
\clearpage
```

# Álgebra Lineal 

## Espacios

Un espacio matemático es un conjunto de elementos al que se le añade una determinada estructura. Por ejemplo, el espacio euclidiano es el espacio plano y sin curvatura que usamos en la vida cotidiana, donde las coordenadas son rectas y las distancias se miden con el teorema de Pitágoras.


Cuando decimos *"espacio euclidiano"*, estamos hablando de:

* Un conjunto de puntos (como los puntos en un plano o en un *espacio* tridimensional).

* Una forma de medir distancias entre ellos.

* Una forma de medir ángulos entre ellos.

\vspace{1.5cm}

## Espacios vectoriales

Un espacio vectorial (a veces también llamado espacio *lineal*) $V$ es un conjunto de objetos llamados vectores sobre los cuales es posible realizar dos operaciones fundamentales [@hstark]:

* Aditividad o suma de vectores.
* Multiplicación de un vector por un escalar (Los escalares usados en un espacio vectorial pueden ser reales o complejos)

\newpage

Estas operaciones (suma de vectores y multiplicación por escalar) deben satisfacer un conjunto de propiedades que garantizan un comportamiento algebraico bien definido y consistente en un espacio vectorial $V$.

\vspace{1.5cm}

1. *Conmutatividad de la suma*. Para todo $x,y \in V$: $x+y = y+x$

2. *Asociatividad de la suma*. Para todo $x,y,z  \in V$:

```{=latex}
\vspace{-1.0em}
\[
(x+y)+z=x+(y+z).
\]
```
3. Existencia del *vector cero*: $0 \in V$ tal que para todo $x \in V$: $x+0=x$

4. Existencia del *inverso aditivo*. Para cada  $x \in V$ existe un vector $y \in V$ tal que:

```{=latex}
\vspace{-1.0em}
\[
x+y=0.
\]
```
5. *Asociatividad de la multiplicación por escalares.* Para cada par de escalares $\alpha, \beta$ y cada $x \in V$

```{=latex}
\vspace{-1.0em}
\[
(\alpha \beta)x = \alpha(\beta x)
\]
```
6. *Distributividad de la multiplicación escalar*: $\alpha(x+y) = \alpha x+ \alpha y$

7. *Distributividad respecto de la suma de escalares.* Para cada par de escalares $\alpha, \beta$ y cada $x \in V$ : $(\alpha + \beta )x = \alpha x+ \beta x$

8. Existencia del elemento identidad. Por  cada $x \in V, 1x=x$ 

\newpage 
Los elementos de un espacio vectorial no tienen que ser vectores geométricos.
Es decir: *"vector"* no significa necesariamente una flecha o una tupla de números. Un vector es simplemente un elemento de un espacio vectorial.

Por ejemplo, pueden ser vectores: polinomios, matrices, funciones, sucesiones,
señales, etc. En matemáticas, se pueden todos ellos abstraer con la noción única
e inmaterial de espacios vectoriales. La abstracción es el precio de
la generalización.

En síntesis: a pesar del nombre espacio vectorial, los elementos de un espacio vectorial no tienen que ser necesariamente vectores geométricos. Pueden ser objetos matemáticos de naturaleza muy diversa, siempre que sea posible definir sobre ellos las operaciones de suma y multiplicación por escalares y que estas satisfagan las propiedades anteriores. 

\vspace{2.5cm}


### Subespacio vectorial

Sea $V$ un espacio vectorial y $W$ un subconjunto no vacío de $V$. El conjunto $W$ es un subespacio vectorial de $V$ **si y solo si** satisface las siguientes propiedades:

* La suma de dos vectores cualesquiera de $W$ pertenece nuevamente a $W$. (Cerrado bajo la suma)
* El producto de cualquier vector de  $W$ por un escalar también pertenece a $W$. (Cerrado sobre la multiplicación por escalares)

\newpage 
### Ejemplos de espacios vectoriales


#### El Plano $\mathbb{R}^2$ y el espacio tridimensional $\mathbb{R}^3$.

Note que tambien un plano que pasa por el origen es un subespacio del
espacio tridimensional.

#### El espacio vectorial de las matrices cuadradas de $n \times n$

Un subespacio de este espacio serian las matrices triangulares inferiores. Lo mismo ocurre con las matrices diagonales.


#### Espacio vectorial de los polinomios reales $\mathcal{P}$.

Un polinomio real es una expresion de la forma $a_nx^n+a_{n-1}x^{n-1}+\ldots+a_0$. El conjunto de tales polinomios forma un espacio vectorial bajo las siguientes operaciones: si 
***a*** = $a_nx^n+a_{n-1}x^{n-1}+\ldots+a_0$ y ***b*** = $b_mx^m+b_{m-1}x^{m-1}+\ldots+b_0$  son elementos de $\mathcal{P}$ (asumiendo que $m<n$), entonces:


```{=latex}
\[
a+b = a_nx^n+\ldots+(a_m+b_m)x^m+\ldots+(a_0+b_0) 
\]
```

y 


```{=latex}
\[
\beta a = \beta a_nx^n+ \beta a_{n-1}x^{n-1}+\ldots+ \beta a_0
\]
```


son elementos de $\mathcal{P}$. Note que aquí cada polinomio es tratado como un vector. Como ejemplo de subespacio, el conjunto de polinomios 
$a_nx^n+a_{n-1}x^{n-1}+\ldots+a_2x^2+a_0$ forma un subespacio de $P(x)$. Es decir, todos los elementos de este subespacio comparten la propiedad de que $a_1=0$


####  El espacio vectorial de funciones reales.


Sea

```{=latex}
\[
F(\mathbb{R})
\]
```

el conjunto de todas las funciones con valores reales definidas sobre los números reales. Este conjunto constituye un espacio vectorial si se definen las operaciones de suma y multiplicación por un escalar de la siguiente manera.

Sean

```{=latex}
\[
f=f(x), \qquad g=g(x)
\]
```

dos funciones cualesquiera y sea $\alpha$ un número real. Entonces:

* La ***suma*** de funciones se define por

```{=latex}
\[
(f+g)(x)=f(x)+g(x).
\]
```

* La ***multiplicación de una función por un escalar*** se define por

```{=latex}
\[
(\alpha f)(x)=\alpha\ f(x).
\]
```

Estas definiciones son válidas para todo $x \in \mathbb{R}$.

**Observación.** En este contexto, cada **función completa** se considera un vector. Es decir, el vector no es el valor que toma la función en un punto determinado, sino la función entera.

Como ejemplo de subespacio, el conjunto de todas las **funciones continuas** definidas sobre $\mathbb{R}$ forma un subespacio de
$F(\mathbb{R})$

\newpage

## Bases


Una base de un espacio vectorial $V$ es un conjunto de vectores que:

1. Genera todo $V$.
2. Es linealmente independiente.


## Dimensión

Dimensión es el número de vectores que tiene una base del espacio vectorial. Por ejemplo, 
una base de $\mathbb R^3$  puede ser:

```{=latex}
\[
\{(1,0,0),(0,1,0),(0,0,1)\}
\]
```
Como tiene tres vectores, $dim(\mathbb R^3)=3$. La dimensión indica cuántas direcciones independientes se necesitan para generar todo el espacio.

## Span 

Dado cualquier espacio vectorial $V$ 
(sea de lo que sea: números, funciones, polinomios, matrices, etc.)
 y un conjunto de vectores ${v1,v2,...,vk}$
 que pertenecen a $V$, el span de esos vectores es:

 ```{=latex}
\[
\operatorname{span}\{v_1,v_2,\ldots,v_k\}
=
\{
a_1v_1+a_2v_2+\cdots+a_kv_k \mid 
a_1,a_2,\ldots,a_k\in\mathbb{F}
\}
\]
```
 
Es decir, el span es el conjunto de todas las combinaciones lineales que se
pueden hacer con ${v1,v2,...,vk}$ .Esto se define para cualquier espacio vectorial, sin importar su naturaleza. $\mathbb{F}$ se lee como el *cuerpo* (*field*) de escalares.

\newpage
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

