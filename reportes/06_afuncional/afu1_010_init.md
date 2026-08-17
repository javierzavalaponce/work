```{=latex}
\clearpage
```

# Motivación

El análisis funcional es una rama de las matemáticas que tiene como idea central el 
estudio de funciones como si fueran *"puntos"* en un espacio. Proporciona las herramientas para medir distancias entre funciones, saber si una función se parece a otra, y si una función *"converge"* (se acerca) a un objetivo. 

El control de sistemas no lineales necesita del análisis funcional debido a que:

1. Los sistemas no lineales se describen con ecuaciones diferenciales (funciones que cambian en el tiempo). El análisis funcional permite tratar toda la trayectoria futura del sistema como un solo objeto matemático.

2. La *estabilidad* se define con distancias entre funciones. Una *norma* es una forma de medir el "tamaño" de una función. Para garantizar que el sistema no se descontrole, usamos normas funcionales que miden la *energía* o la *máxima desviación* de la señal de error.

3. El controlador se diseña como un *operador* (una función que transforma funciones). Un controlador no es más que una regla matemática que toma la salida del sistema y produce una entrada (una orden al sistema). En análisis funcional, esto es un operador: una máquina que toma una función (la medición) y devuelve otra función (la orden). Con análisis funcional, se puede demostrar que ese operador (el controlador) es continuo (no da saltos bruscos) y acotado (no produce órdenes imposibles). 

\vspace{1.5cm}


*En el control de sistemas no lineales, el análisis funcional nos provee de normas que sirven como 'certificados de estabilidad', transformando un problema dinámico complejo en un problema de acotación de operadores en espacios de funciones.*


# Teoría de Conjuntos 

Las formas principales de describir un conjunto son:

1. Por *extensión*: Se enumeran todos sus elementos. 
   Ejemplo: A = {2, 4, 6, 8} 

2. Por *comprensión*: Se describe la propiedad que cumplen todos sus elementos. Ejemplo: A = { x | x es un número par menor 10}  

3. Por *pertenencia*. Ejemplo: Sea L el conjunto de estudiantes en esta aula con más de 3 metros de altura. L = $\emptyset$ o  {} (Conjunto vacío)

## Pertenencia y subconjuntos:

* Pertenencia $\in$

El Axioma de Extensionalidad establece que los conjuntos son determinados exclusivamente por su extensión, es decir, por el conjunto de elementos que contienen.

```{=latex}
\[
\forall A \, \forall B \,
\left(
\forall x \,
(x \in A \iff x \in B)
\;\rightarrow\;
A = B
\right).
\]
```

* Union $\cup$

La unión de dos conjuntos $A$ y $B$ es el conjunto formado por todos los elementos que pertenecen a $A$, a $B$, o a ambos. Se define como:

```{=latex}
\[
A \cup B = \{ x \mid \forall x \in A \lor x \in B\}
\]
```


* Interseccion $\cap$

La intersección de dos conjuntos $A$ y $B$ es el conjunto formado por todos los elementos que pertenecen simultáneamente tanto a $A$ como a $B$. Se define como:

```{=latex}
\[
A \cap B = \{ x \mid \forall x \in A \land x \in B\}
\]
```

* Complemento $A^c$

Se trabaja con el complemento relativo. Fijando un conjunto universo $U$ (que debe estar definido previamente en el contexto en el que trabajamos), el complemento de $A$ respecto a $U$ se define como:

```{=latex}
\[
A^c = U \setminus A = \{ x \in U \mid x \notin A \}
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



