```{=latex}
\clearpage
```

# Preparacion de clase de 21 sep 2026

En matemáticas, un espacio es un conjunto de elementos sobre el que se han definido determinadas operaciones, relaciones o propiedades que permiten estudiarlo desde un punto de vista particular.


```{=latex}
\[
\text{conjunto}+\text{propiedades}=\text{espacio matemático}
\]
```

por ejemplo:

* conjunto + una distancia $\rightarrow$ espacio métrico
* conjunto + operaciones de suma y multiplicación por escalares $\rightarrow$  espacio vectorial
* espacio vectorial + una norma $\rightarrow$  espacio normado
* espacio vectorial + un producto interno $\rightarrow$  espacio con producto interno
* espacio normado completo $\rightarrow$  espacio de Banach

\begin{center}
\rule{0.7\textwidth}{0.4pt}
\end{center}

Un espacio vectorial (a veces también llamado espacio *lineal*) $V$ es un conjunto de objetos llamados vectores sobre los cuales es posible realizar dos operaciones fundamentales [@hstark]:

* Aditividad o suma de vectores.
* Multiplicación de un vector por un escalar (Los escalares usados en un espacio vectorial pueden ser reales o complejos)

Estas operaciones (suma de vectores y multiplicación por escalar) deben satisfacer un conjunto de propiedades que garantizan un comportamiento algebraico bien definido y consistente en un espacio vectorial $V$.


\begin{center}
\rule{0.7\textwidth}{0.4pt}
\end{center}

Los elementos de un espacio vectorial no tienen que ser vectores geométricos.
Es decir: *"vector"* no significa necesariamente una flecha o una tupla de números. Un vector es simplemente un elemento de un espacio vectorial.

Por ejemplo, pueden ser vectores: polinomios, matrices, funciones, sucesiones,
señales, etc. En matemáticas, se pueden todos ellos abstraer con la noción única
e inmaterial de espacios vectoriales. La abstracción es el precio de
la generalización.

En síntesis: a pesar del nombre espacio vectorial, los elementos de un espacio vectorial no tienen que ser necesariamente vectores geométricos. Pueden ser objetos matemáticos de naturaleza muy diversa, siempre que sea posible definir sobre ellos las operaciones de suma y multiplicación por escalares y que estas satisfagan laspropiedades endiores. 


\begin{center}
\rule{0.7\textwidth}{0.4pt}
\end{center}

Ejemplos de espacios vectoriales:

1. El Plano $\mathbb{R}^2$ y el espacio tridimensional $\mathbb{R}^3$.

2. El espacio vectorial de las matrices cuadradas de $n \times n$
Un subespacio de este espacio serian las matrices triangulares inferiores. Lomismo ocurre con las matrices diagonales.

3. Espacio vectorial de los polinomios reales $\mathcal{P}$.

\begin{center}
\rule{0.7\textwidth}{0.4pt}
\end{center}

* Base

Una base de un espacio vectorial $V$ es un conjunto de vectores que:
1. Genera todo $V$.
2. Es linealmente independiente.


* Dimensión

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

