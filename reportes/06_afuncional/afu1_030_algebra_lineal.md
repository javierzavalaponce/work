```{=latex}
\clearpage
```

# Álgebra Lineal 

## Espacios vectoriales

Un espacio vectorial (a veces también llamado espacio *lineal*) $V$ es un conjunto de objetos llamados vectores sobre los cuales es posible realizar dos operaciones fundamentales [@hstark]:

* Suma de vectores.
* Multiplicación de un vector por un escalar (Los escalares usados en un espacio vectorial pueden ser reales o complejos)

Estas operaciones deben satisfacer un conjunto de propiedades que garantizan un comportamiento algebraico consistente.

1. Conmutatividad de la suma. Para todo $x,y \in V$:

```{=latex}
\[
x+y = y+x
\]
```

2. Asociatividad de la suma. Para todo $x,y,z  \in V$:

```{=latex}
\[
(x+y)+z=x+(y+z).
\]
```

3. Existe un vector $0 \in V$ tal que para todo $x \in V$:

```{=latex}
\[
x+0=x
\]
```

4. Existencia del inverso aditivo. Para cada  $x \in V$ existe un vector $y \in V$ tal que:

```{=latex}
\[
x+y=0.
\]
```

5. Asociatividad de la multiplicación por escalares. Para cada par de escalares $a,b$ y cada $x \in V$

```{=latex}
\[
(ab)x = a(bx)
\]
```

6. Distributividad de la multiplicación escalar.

```{=latex}
\[
a(x+y) = ax+ay
\]
```

7. Distributividad respecto de la suma de escalares. Para cada par de escalares $a,b$ y cada $x \in V$

```{=latex}
\[
(a+b)x = ax+bx
\]
```

8. Existencia del elemento identidad. Por  cada $x \in V$ 

```{=latex}
\[
1x=x
\]
```


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


#### Espacio vectorial de los polinomios reales $P(x)$.

Un polinomio real es una expresion de la forma $a_nx^n+a_{n-1}x^{n-1}+\ldots+a_0$. El conjunto de tales polinomios forma un espacio vectorial bajo las siguientes operaciones: si 
***a*** = $a_nx^n+a_{n-1}x^{n-1}+\ldots+a_0$ y ***b*** = $b_mx^m+b_{m-1}x^{m-1}+\ldots+b_0$  son elementos de $P(x)$ (asumiendo que $m<n$), entonces:


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


son elementos de $P(x)$. Note que aquí cada polinomio es tratado como un vector. Como ejemplo de subespacio, el conjunto de polinomios 
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

Analogía: la base de un espacio vectorial 

 cómo construyes una pared una pared no es que vengan todos juntos bueno a menos que lo
cueles y ya es otro rollo pero cómo construyes tradicionalmente una pared agarras los tabiques
que son de la misma forma y los vas acomodando los va sumando
pero como es el mismo es alargado o sea por ejemplo una fila de 10 tabiques podemos ir
sumando o ese tabique si lo multiplicamos por 10 ya me da la fila esa es la idea los tabiques dentro
de un espacio vectorial van a ser los vectores que sean linealmente independientes y además que
todo todo todo todo todo todo todo el espacio no importa qué vector agarres no importa que
agarres el vector más extraño de ese espacio con esos tabiques tú dices a mirar ver esa casa
de ahí esa esa barda ese muro no importa qué tan grande sea el muro y es ah pues sí yo no puedo
formar con esos tabiques quizá ocupe mil tabiques quizá ocupe pita viques quizá ocupe fita viques
e tabiques pero con ese tabique puedo construir ese gran muro entonces cuando yo quiero estudiar
ese gran muro lo puedo estudiar con esos tabiques sus propiedades eso es lo importante la base
conociendo la forma en la que voy a estar construyendo todo el espacio vectorial no me tengo que
fijar solamente en esa pared me fijo en la base la base lleva toda la información del espacio
vectorial punto si un espacio vectorial es un universo su base es como su conjunto de átomos
o bloques de construcción fundamentales con una base podemos construir cualquier otro elemento de
ese universo debe de cumplir lo siguiente es un conjunto de vectores llamamos le ve que son
b 1 b 2 b 3 hasta b n es una base de b si los vectores de b son linealmente independientes y los
vectores de b generan al espacio vectorial vámonos con los ejemplos en r 2 los vectores y y j que
serían el 0 1 y el 1 es que serían el 0 y 1 y 1 0 forman una base forman una base cualquier
otro vector en el plano se puede expresar como una combinación de estos dos como la base tiene
dos vectores decimos que la dimensión de r 2 es 2 y aquí el truco el número de elementos que tiene
la base es la definición en la definición de lo que llamamos dimensión del espacio vectorial en
r 3 necesitamos tres vectores base y jk 001 0 1 0 y 1 0 0 por lo tanto su dimensión es 3 la
dimensión es simplemente el número de vectores que necesitas en tu base y para los espacios más
abstractos el espacio de matrices de 2 por 2 tiene una base de 4 matrices 1 0 0 0 nota las
entradas el 1 se va alternando por lo tanto su dimensión es 4 en general la dimensión por
ejemplo de r n es n y la dimensión del espacio de matrices de tamaño n por m es n por m bueno


Bases y Dimensión: Saber que si un espacio tiene base de nn elementos, todo vector se escribe de forma única como combinación de esa base. (En análisis funcional, esto se extiende a infinitas sumas).

## Dimensión


Funciones que respetan suma y producto. 
Núcleo (kernel) e imagen.
Matriz asociada (concepto de *linealidad*).

## Producto interno 

Angulos ortogonalidad. 
(Sección 1.4) de [@hstark]
