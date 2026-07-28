```{=latex}
\clearpage
```
# Teoría de Conjuntos 

Las formas principales de describir un conjunto son:

1. Por *extensión*: Se enumeran todos sus elementos. 
   Ejemplo: A = {2, 4, 6, 8} 

2. Por *comprensión*: Se describe la propiedad que cumplen todos sus elementos. Ejemplo: A = { x | x es un número par menor 10}  

3. Por *pertenencia*. Ejemplo: Sea L el conjunto de estudiantes en esta aula con más de 3 metros de altura. L = $\emptyset$ o  {} (Conjunto vacío)

## Pertenencia y subconjuntos:

Pertenencia $\in$

Union $\cup$

Interseccion $\cap$

Complemento $A^c$

(8484: desarrollar un poco mas esta seccion...)

## Conjuntos finitos

Un conjunto es finito cuando posee un número limitado de elementos.
Por ejemplo, $A$ contiene cuatro elementos:

```{=latex}
\[
A=\{2,5,7,11\}
\]
```

\newpage 
## Conjuntos infinitos

Un conjunto es infinito cuando no es posible enumerar todos sus elementos.
```{=latex}
\[
\begin{aligned}
\mathbb N&=\{1,2,3,4,\ldots\} \\
\mathbb Z&=\{\ldots,-2,-1,0,1,2,\ldots\} \\
\mathbb Q&=\{\frac pq \mid p,q\in\mathbb Z,\ q\neq0\} \\
\end{aligned}
\]
```
Aunque todos ellos son infinitos, no todos poseen el mismo tamaño.


## Conjuntos numerables

Un conjunto se dice numerable (o contablemente infinito) cuando sus elementos pueden ponerse en correspondencia uno a uno con los números naturales.

Es decir, es posible escribir sus elementos como una sucesión

```{=latex}
\[
j_1, j_2, j_3,\ldots
\]
```

En otras palabras, existe una función biyectiva

```{=latex}
\[
f:\mathbb N\longrightarrow A.
\]
```



## Producto cartesiano de conjuntos

Dados dos conjuntos $A$ y $B$, el producto cartesiano es el conjunto de todos los pares ordenados $(a,b)$ donde $a \in A$ y $b \in B$:

```{=latex}
\[
A \times B =
\{(a,b) \mid a ∈ A \text{ y } b ∈ B\}
\]
```

### Función

Funciones,dominio, codominio, imagen.
Función inyectiva, sobreyectiva y biyectiva. 
Un *operador* en análisis funcional es una función entre espacios de vectores.



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


* ***Recorrido*** (o Imagen): Es el conjunto de todas las segundas componentes: $Rec(R)$

*Ejemplo:*

Sea $A=\{1,2,3\}$ , $B=\{x,y\}$ y $R=\{(1,x),(1,y),(2,x)\}$. $R$ es una relación porque es un subconjunto de $A \times B$



