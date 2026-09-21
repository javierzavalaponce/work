```{=latex}
\clearpage
```

# Álgebra Lineal 


\vspace{4.5cm}

\begin{figure}[H]
\centering
\includegraphics[width=0.63\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/mictlantecuhtli.png}
\end{figure}



\newpage
## Espacios

En matemáticas, un espacio puede entenderse, en primera aproximación, como un conjunto de elementos al que se le proporciona una estructura matemática. Esta estructura consiste en definir determinadas relaciones, operaciones o propiedades sobre los elementos del conjunto, de manera que podamos trabajar con ellos y estudiar su comportamiento.

Por ejemplo, un conjunto de puntos puede convertirse en un *espacio* cuando, además de considerar sus puntos, disponemos de una forma de medir distancias y ángulos entre ellos. Estas nociones permiten hablar de longitudes, perpendicularidad, rectas, etc.


Cuando hablamos del espacio $\mathbb{R}^2$  que conocemos de la geometría elemental, estamos considerando:

* un conjunto de puntos, como los puntos de un plano o del espacio tridimensional;
* una forma de medir la distancia entre dos puntos y 
* una forma de medir ángulos entre direcciones o segmentos.

\vspace{2.5cm}

En el espacio $\mathbb{R}^2$, la distancia está relacionada con el teorema de Pitágoras. Por ejemplo, en el plano, si dos puntos tienen coordenadas $(x_1,y_1)$ y $(x_2,y_2)$, su distancia es

```{=latex}
\[
d=\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}
\]
```

Así, la palabra espacio no se refiere solamente a un conjunto de elementos. Se refiere al conjunto *junto* con la estructura matemática que se ha definido sobre él.

\newpage

## Espacios vectoriales

Un espacio vectorial (a veces también llamado espacio *lineal*) $V$ es un conjunto de objetos llamados vectores sobre los cuales es posible realizar dos operaciones fundamentales [@hstark]:

* Aditividad o suma de vectores.
* Multiplicación de un vector por un escalar (Los escalares usados en un espacio vectorial pueden ser reales o complejos)

Estas operaciones (suma de vectores y multiplicación por escalar) deben satisfacer un conjunto de propiedades que garantizan un comportamiento algebraico bien definido y consistente en un espacio vectorial $V$.

```{=latex}
\begin{equation}
Propiedades:
\label{eq:props_espacios_vectoriales}
\end{equation}
```

\vspace{1.0cm}

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
**Observación:**

Los elementos de un espacio vectorial no tienen que ser vectores geométricos.
Es decir: *"vector"* no significa necesariamente una flecha o una tupla de números. Un vector es simplemente un elemento de un espacio vectorial.

Por ejemplo, pueden ser vectores: polinomios, matrices, funciones, sucesiones,
señales, etc. En matemáticas, se pueden todos ellos abstraer con la noción de espacios vectoriales.

En síntesis: a pesar del nombre espacio vectorial, los elementos de un espacio vectorial no tienen que ser necesariamente vectores geométricos. Pueden ser objetos matemáticos de naturaleza muy diversa, siempre que sea posible definir sobre ellos las operaciones de suma y multiplicación por escalares y que estas operaciones satisfagan las propiedades de la página anterior.


\vspace{1.5cm}

### Subespacio vectorial

Sea $V$ un espacio vectorial y $W$ un subconjunto no vacío de $V$. El conjunto $W$ es un subespacio vectorial de $V$ **si y solo si** satisface las siguientes propiedades:

* La suma de dos vectores cualesquiera de $W$ pertenece nuevamente a $W$. (Cerrado bajo la suma)
* El producto de cualquier vector de  $W$ por un escalar también pertenece a $W$. (Cerrado sobre la multiplicación por escalares)

\newpage 
## Ejemplos de espacios vectoriales


\vspace{1.0cm}

### El Plano $\mathbb{R}^2$ y el espacio tridimensional $\mathbb{R}^3$.
El plano es un subespacios del espacio tridimensional.

### El espacio vectorial de las matrices cuadradas de $n \times n$
Un subespacio de este espacio son las matrices diagonales.


### Espacio vectorial de los polinomios reales $\mathcal{P}$.

Un polinomio real es una expresion de la forma:

```{=latex}
\[
a_nx^n+a_{n-1}x^{n-1}+\ldots+a_0
\]
```

El conjunto de tales polinomios forma un espacio vectorial. 

```{=latex}
\[
u = a_nx^n+a_{n-1}x^{n-1}+\ldots+a_0
\]
```


```{=latex}
\[
v = b_mx^m+b_{m-1}x^{m-1}+\ldots+b_0
\]
```

Si $u$ y $v$ son elementos de $\mathcal{P}$ (asumiendo que $m<n$), entonces:

```{=latex}
\[
\underbrace{u+v}_{\text{suma de vectores}}
= 
a_nx^n+\ldots+(a_m+b_m)x^m+\ldots+(a_0+b_0) 
\]
```

y 


```{=latex}
\[
\underbrace{\beta a }_{\text{mult. por escalar}}
= 
\beta a_nx^n+ \beta a_{n-1}x^{n-1}+\ldots+ \beta a_0
\]
```
son elementos de $\mathcal{P}$. Note que aquí cada polinomio es tratado como un vector. 

\newpage
###  El espacio vectorial de funciones reales.


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

## Base


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
pueden hacer con ${v1,v2,...,vk}$ .Esto se define para cualquier espacio vectorial, sin importar 
su naturaleza. $\mathbb{F}$ se lee como el *cuerpo* (*field*) de escalares.



**Ejemplos de *span* en otros espacios**

Más adelante, en analisis funcional, se abordara el *span* de otros espacios, por ejemplo:

* Espacio de polinomios $P_2(x)$. Tomamos los vectores : $\{1,x,x^2\}$:
 El span son todos los polinomios de grado menor o igual a 2: $a+bx+cx^2$

* Espacio de funciones trigonométricas. Tomamos los 
vectores: $\{sin⁡(x),cos⁡(x)\}$. El span 
son todas las funciones de la forma: $\alpha sin⁡(x)+ \beta cos⁡(x)$


	
\newpage

## Producto punto (o producto interno) y norma

El producto interno es una operación que toma dos vectores
y produce un número real. Con $x$ , $y$ como elementos (*vectores*)  $\in V$ 

```{=latex}
\[
\langle\cdot,\cdot\rangle:V\times V\longrightarrow\mathbb{R}
\]
```   

```{=latex}
\[
(x,y)\longrightarrow \langle x,y\rangle
\]
```


Aunque su definición en $\mathbb R^n$ se expresa mediante
una suma de productos de sus componentes, este *número* también
contiene información geométrica sobre la relación entre los
vectores, particularmente sobre el ángulo que forman.

En $\mathbb R^n$, el producto interno usual está definido por

```{=latex}
\[
\boxed{
\langle x,y\rangle
=
x_1y_1+x_2y_2+\cdots+x_ny_n
}
\]
```
\vspace{1.0cm}

Tomemos por ejemplo, dos vectores $u$, $v$ en $\mathbb R^2$ 

```{=latex}
\[
u=(1,2),\qquad v=(3,4),
\]
```
entonces

```{=latex}
\[
\langle u,v\rangle
=
(1)(3)+(2)(4)
=
11.
\]
```

\vspace{1.5cm}
\begin{figure}[H]
\centering
\includegraphics[width=0.21\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/Miquiztli.png}
\end{figure}


\newpage

La ***norma*** de un vector es, esencialmente, su longitud o magnitud. En $\mathbb R^2$ se usa el teorema de Pitágoras,
 por ejemplo, el vector $(1,1)$ tiene longitud $\sqrt{2}$. Se usa la doble barra para denotar la norma. Entonces: 
$u=(1,1)$, $\|u\| = \sqrt{2}$ 

Es importante distinguir entre el producto interno y la norma. El producto interno toma dos vectores y produce un número: $\langle u,v\rangle$.
La norma, en cambio, asigna una longitud a un solo vector: $\|u\|$.

La norma puede obtenerse a partir del producto interno mediante: $\|u\|=\sqrt{\langle u,u\rangle}$

En $\mathbb R^n$, la norma habitual es

```{=latex}
\[
\|\mathbf{v}\|
=
\sqrt{v_1^2+v_2^2+\cdots+v_n^2}
\]
```

Más adelante veremos que no existe una única norma. Hay normas 1, 2, infinito, etc., y eso será muy importante para análisis funcional.

\newpage

Por otro lado, (*ver demostración de la siguiente sección*) para vectores $x=(x_1,x_2)$ y $y=(y_1,y_2)$

```{=latex}
\[
\boxed{
\langle x,y\rangle = \|x\| \|y\| \cos\theta
}
\]
```

Para:

```{=latex}
\[
x=(1,2),\qquad y=(3,4),
\]
```
\begin{figure}[H]
\centering
\includegraphics[width=0.6\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/pp34.png}
\caption{Angulo $\theta$ entre $x$ , $y$ = $arccos(\frac{5\sqrt{5}}{11}) \approx 10.3^\circ$   }
\label{fig:ppunt34}
\end{figure}

\vspace{0.2cm}
\begin{figure}[H]
\centering
\includegraphics[width=0.21\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/Ocelotl.png}
\end{figure}


\newpage

## Conexión entre ley de cosenos, norma y producto punto

Tomemos los vectores $\mathbf{u}$ y $\mathbf{v}$ con el mismo origen. 
El vector que va de la punta de $\mathbf{u}$ a la punta de $\mathbf{v}$ es $\mathbf{v} - \mathbf{u}$.

Los tres vectores forman un triángulo cuyos lados miden:

* $\|\mathbf{u}\|$
* $\|\mathbf{v}\|$
* $\|\mathbf{v} - \mathbf{u}\|$

El ángulo entre $\mathbf{u}$ y $\mathbf{v}$ es $\theta$, y por la **Ley de los Cosenos**:

```{=latex}
\[
\|\mathbf{v} - \mathbf{u}\|^2 = \|\mathbf{u}\|^2 + \|\mathbf{v}\|^2 - 2\|\mathbf{u}\|\|\mathbf{v}\|\cos\theta
\]
```

Ahora calculamos $\|\mathbf{v} - \mathbf{u}\|^2$ usando coordenadas:

```{=latex}
\[
\|\mathbf{v} - \mathbf{u}\|^2 = (v_1 - u_1)^2 + (v_2 - u_2)^2
\]
```


Expandimos:

```{=latex}
\[
= v_1^2 - 2u_1v_1 + u_1^2 + v_2^2 - 2u_2v_2 + u_2^2
\]
```

Agrupamos:

```{=latex}
\[
= (u_1^2 + u_2^2) + (v_1^2 + v_2^2) - 2(u_1v_1 + u_2v_2)
\]
```

```{=latex}
\[
= \|\mathbf{u}\|^2 + \|\mathbf{v}\|^2 - 2(u_1v_1 + u_2v_2)
\]
```

\newpage

**Igualando las dos expresiones**

De la Ley de Cosenos:

```{=latex}
\[
\|\mathbf{v} - \mathbf{u}\|^2 = \|\mathbf{u}\|^2 + \|\mathbf{v}\|^2 - 2\|\mathbf{u}\|\|\mathbf{v}\|\cos\theta
\]
```

De las coordenadas:

```{=latex}
\[
\|\mathbf{v} - \mathbf{u}\|^2 = \|\mathbf{u}\|^2 + \|\mathbf{v}\|^2 - 2(u_1v_1 + u_2v_2)
\]
```

Como ambos lados son iguales a lo mismo, igualamos:

```{=latex}
\[
\|\mathbf{u}\|^2 + \|\mathbf{v}\|^2 - 2\|\mathbf{u}\|\|\mathbf{v}\|\cos\theta
=
\|\mathbf{u}\|^2 + \|\mathbf{v}\|^2 - 2(u_1v_1 + u_2v_2)
\]
```

Cancelamos $\|\mathbf{u}\|^2 + \|\mathbf{v}\|^2$ en ambos lados:

```{=latex}
\[
-2\|\mathbf{u}\|\|\mathbf{v}\|\cos\theta = -2(u_1v_1 + u_2v_2)
\]
```

Dividimos entre $-2$:

```{=latex}
\[
\boxed{u_1v_1 + u_2v_2 = \|\mathbf{u}\|\|\mathbf{v}\|\cos\theta}
\]
```




