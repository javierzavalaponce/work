\newpage
```{=latex}
\appendix
```

# Apéndice: Fundamentos


\vspace{1cm}

## Lógica proposicional

La lógica proposicional es un sistema formal cuyos elementos básicos son proposiciones atómicas y conectores lógicos, mediante los cuales se construyen proposiciones compuestas cuyo valor de verdad depende únicamente del valor de verdad de sus componentes. Una proposición es un enunciado declarativo, una afirmación cuyo significado está completamente determinado y se le puede asignar un único valor: verdadero o falso.

Ejemplo, sean las proposiciones:

* P: "Está lloviendo"
* Q: "La calle está mojada"


Podemos construir:

* $P \land Q$ (P y Q)
* $P \lor Q$ (P o Q)
* $P \rightarrow Q$ (Si P, entonces Q)
* $\neg P$ (No P)

La proposición: *"La luna es de queso"*, si bien *falsa*, no deja de ser una proposición.

La proposición: $x > 5$ no es una proposición válida sin conocer el valor de $x$
ya que no podemos estimar si es verdadera o falsa.

*Nota adicional*:

* "Snow is white."
* "La nieve es blanca."
* "Schnee ist weiß."

Son tres enunciados distintos pero representan la misma proposición.

\newpage

## Lógica de primer orden (Lógica de predicados)

En la lógica de primer, además de conectores lógicos, se incorporan variables, funciones, predicados y cuantificadores para expresar propiedades de los elementos de un *dominio* y las relaciones entre ellos. 

### Dominio

Es el conjunto de objetos sobre los cuales estamos hablando. Ejemplos de dominio: personas, números naturales, números reales, vectores, matrices, funciones, etc. Por ejemplo, en programación. Supongamos que nuestro universo está formado por tres personas:

``` python
alumnos = [
    {"nombre": "Juan",  "estudiante": True,  "aprobo": True},
    {"nombre": "María", "estudiante": True,  "aprobo": True},
    {"nombre": "Pedro", "estudiante": False, "aprobo": False},
]
```

### Variables

Representan un objeto cualquiera del dominio.

### Predicados


Un predicado representa una propiedad o relación. Por ejemplo: $E(x)$
significa: *"x es estudiante"*. En programación, un predicado puede verse como una función que devuelve un valor booleano.

``` python
def E(x):
    return x["estudiante"]
```
### Ejemplo
Sea

* $E(x)$: "x es estudiante."
* $A(x)$: "x aprobó."

Todo estudiante aprobó: $\forall x(E(x) \rightarrow A(x))$ 

\newpage
## Construcción de los números en ZFC.

Todo objeto matemático puede representarse como un conjunto, y toda la matemática puede desarrollarse a partir de unos pocos axiomas sobre conjuntos. 

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

\vspace{2cm}


Existe más de una teoría axiomática de conjuntos aunque la más conocida y utilizada es la teoría ZFC, existen muchas otras alternativas,
Las tres grandes: ZFC, NBG y MK. 

Para la inmensa mayoría de las matemáticas, incluyendo el análisis funcional, la base es la teoría ZFC (Zermelo-Fraenkel con el Axioma de Elección), es decir, ZFC puede verse como el suelo firme y conocido sobre el que se asienta la mayor parte de las matemáticas.

\newpage
### Cardinalidad

La cardinalidad es un concepto que intenta responder a la pregunta:
*¿Cuántos elementos tiene un conjunto?*

La cardinalidad de $A=\{2,5,7,11\}$, denotada por $|A|$ es 4.
    
#### Cardinalidad numerable

Cuando el conjunto es infinito, la cardinalidad nos permite comparar el tamaño de conjuntos infinitos. Si bien a primera vista podria parecer que el conjunto de los enteros $\mathbb Z$ es mas grande que el de los naturales $\mathbb N$. En teoría de conjuntos no se cuentan los elementos uno por uno. En lugar de ello se intenta construir una correspondencia uno a uno (una *biyección*).

Si existe una biyección 

```{=latex}
\[
f:A\longrightarrow B
\]
```
entonces ambos conjuntos tienen exactamente la misma cardinalidad.

Retomando el caso de los naturales y los enteros,
Podemos emparejar cada natural con exactamente un entero:

| Naturales    | Enteros       |
| ------------ | ------------- |
|  1 |  0  |
|  2 |  1  |
|  3 | -1  |
|  4 |  2  |
|  5 | -2  |
|  6 |  3  |
|  7 | -3  |

:  No sobra ningún elemento en ninguno de los dos conjuntos.

La cardinalidad de un conjunto numerable se representa mediante el símbolo $\aleph_0$ y se lee: *"aleph cero"*.

```{=latex}
\[
|\mathbb{N}| = |\mathbb{Z}| = \aleph_0
\]
```


#### Cardinalidad del continuo

Con los números reales ocurre algo distinto. Cantor demostró que es imposible enumerarlos. Su cardinalidad es $\mathfrak{c}$ 
llamada cardinalidad del continuo.

Se cumple 
```{=latex}
\[
|\mathbb R| = \mathfrak{c}
\]
```

Además,

```{=latex}
\[
\aleph_0 < \mathfrak{c}
\]
```

Es decir, hay estrictamente más números reales que números naturales.

\newpage


## Producto cartesiano en python


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


