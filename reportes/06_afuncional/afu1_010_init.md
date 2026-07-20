```{=latex}
\clearpage
```


# Fundamentos

\vspace{1cm}

## Lógica proposicional.

La base.
Ejemplos de proposiciones:

## Lógica de primer orden.

El lenguaje universal de las matemáticas.
Es el lenguaje estándar que usan los matemáticos para formalizar las teorías

## Conjunto

Las formas principales de describir un conjunto

1. Por extensión: Se enumeran todos sus elementos. Ejemplo: {2, 4, 6} 

2. Por comprensión: Se describe la propiedad que cumplen todos sus elementos. Ejemplo: A = { x | x es un número par menor 10\

3. Por pertenencia Un conjunto es una entidad matemática que está definida únicamente por la pertenencia. Ejemplo: Sea L el conjunto de estudiantes en esta aula con más de 3 metros de altura. L = $\emptyset$ o  {}


\newpage

## Función y Relación

### Producto cartesiano
Dados dos conjuntos $A$ y $B$, el producto cartesiano es el conjunto de todos los pares ordenados $(a,b)$ donde $a \in A$ y $b \in B$:

```{=latex}
\[
A \times B =
\{(a,b) \mid a ∈ A \text{ y } b ∈ B\}
\]
```
\vspace{1cm}

```python
from itertools import product

# --- Producto de dos listas ---
A = [1, 2]
B = ['a', 'b']

resultado = list(product(A, B)) #product devuelve un iterador
print(resultado)

resultado = [(x, y) for x in A for y in B]
print(resultado)

resultado = []
for x in A:
    for y in B:
        resultado.append((x, y))
print(resultado)
```
\vspace{0.7cm}

Resultado:

```c
[(1, 'a'), (1, 'b'), (2, 'a'), (2, 'b')]
[(1, 'a'), (1, 'b'), (2, 'a'), (2, 'b')]
[(1, 'a'), (1, 'b'), (2, 'a'), (2, 'b')]
```

\vspace{0.7cm}

*Nota:* en ZFC,
$(a,b)$:={{$a$},{$a,b$}}

\newpage

### Relación

Una relación $R$ entre un conjunto $A$ y un conjunto $B$ es cualquier subconjunto del producto cartesiano $A \times B$

```{=latex}
\[
R \subseteq 
A \times B
\]
```

Decimos que *$a$ está relacionado con $b$* y lo escribimos como aRb.

* ***Dominio***: Es el conjunto de todas las primeras componentes: $Dom(R)$



```latex
\[
\operatorname{Dom}(R) = \{\, a \in A \mid \exists\, b \in B : (a,b) \in R \,\}
\]
```

* ***Recorrido*** (o Imagen): Es el conjunto de todas las segundas componentes: $Rec(R)$

*Ejemplo:*

Sea A={1,2,3} y B={x,y}
R={(1,x),(1,y),(2,x)}. Esto es una relación porque es un subconjunto de $A \times B$

\newpage


# Construcción de los números en ZFC.

Todo objeto matemático puede representarse como un conjunto, y toda la matemática puede desarrollarse a partir de unos pocos axiomas sobre conjuntos.

Para que necesitamos axioma?:

```{=latex}
\begin{center}
\rule{0.9\textwidth}{0.4pt}
\rule{0.9\textwidth}{0.4pt}
\end{center}
```

La construcción de von Neumann es la forma estándar de definir los números naturales dentro de la Teoría Axiomática de Conjuntos (ZFC).

A partir del conjunto vacío y utilizando únicamente la operación de *"poner entre llaves"*, se pueden construir todos los números naturales

* El número 0 = $\emptyset$ (el conjunto vacío).
* El número 1 = {$\emptyset$} (el conjunto que contiene al vacío).
* El número 2 = {$\emptyset$, {$\emptyset$}} (el conjunto que contiene al vacío y al 1).

La regla fundamental , el *Sucesor*:


```{=latex}
\[
S(n) = n \cup \{n\}
\]
```

Por ejemplo: 2 = $\{0,1\}$

## Cardinalidad


# Álgebra lineal profunda

## Espacios vectoriales
## Bases
## Dimensión
## Transformaciones lineales

# Geometría de espacios vectoriales
## Norma
## Distancia
## Convergencia

# Espacios de funciones

una función también puede ser un vector.

# Análisis funcional


## Banach
## Hilbert
## Operadores
## Funcionales
## Hahn-Banach
## Riesz
## Espectro







# Definición formal de Espacio Métrico


Un espacio métrico es un par

```{=latex}
\[
(X,d)
\]
```

 donde $X$ es un conjunto abstracto y $d$ es una función ***distancia*** que cumple cuatro axiomas fundamentales:

* es no negativa y finita
* la distancia es cero si y solo si los puntos son iguales
* es simétrica
* cumple la desigualdad triangular (la distancia directa es menor o igual que la suma de distancias indirectas).


Un conjunto es una entidad matemática que no está definida por la naturaleza, el orden, la repetición o las cualidades de sus elementos, sino ***únicamente*** por la pertenencia (quién está dentro y quién está fuera).



Kreyszig (Análisis Funcional)

\newpage






# Ejemplos básicos de espacios métricos

* La recta real y el plano/complejo 
* Los espacios euclidianos Rn y unitarios Cn
* El espacio de sucesiones acotadas (con la métrica del supremo).
* El espacio de funciones continuas C[a,b]C[a,b] (con la métrica del máximo).
* El espacio métrico discreto (donde la distancia entre puntos distintos es siempre 1).


# Espacios de sucesiones $s$ y $lp$ 


# Data-Driven Robust Control

Es posible cerrar el ciclo completo desde la generación automática de un controlador mediante IA hasta su ejecución en tiempo real en un sistema embebido, sin perder el desempeño del controlador.


Las expresiones matemáticas obtenidas mediante algoritmos de inteligencia artificial pueden aproximarse mediante funciones de menor complejidad computacional sin degradar significativamente la estabilidad, robustez y desempeño del sistema de control.


Desarrollar y validar un método matemático para aproximar y transformar controladores generados automáticamente mediante inteligencia artificial, de forma que puedan implementarse eficientemente en sistemas embebidos preservando las propiedades esenciales del control en lazo cerrado.


¿Qué es un espacio vectorial?
¿Qué es una norma (una forma de medir tamaño o distancia)?
¿Qué es un espacio de funciones?
¿Qué es un conjunto convexo?
¿Qué significa proyectar sobre un conjunto convexo?



mapa:
* Lógica
* Teoría de conjuntos (ZFC)
* Álgebra lineal
* Espacios vectoriales
* Normas
* Métrica (distancia)
* Espacios normados
* Espacios de Banach
* Producto interno
* Espacios de Hilbert
* Operadores lineales
* Análisis Funcional


* Espacios vectoriales
* Funciones como vectores
* Normas
* Distancias
* Mejor aproximación
* Proyección
* Conjuntos convexos

