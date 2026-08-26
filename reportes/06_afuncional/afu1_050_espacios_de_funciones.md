```{=latex}
\clearpage
```
# Espacios de funciones

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


## Base del espacio de funciones reales

Aquí hay que distinguir según el tipo de base:

### Base de Hamel (algebraica)

Existe por el axioma de elección (todo espacio vectorial tiene una base de Hamel) pero es una base enormemente infinita. No se puede escribir explícitamente. Además, no es numerable.

### Base de Schauder (topológica, para espacios de Banach/Hilbert)

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


***¿Se puede especificar una base concreta?***	No, salvo ciertos subespacios (como polinomios, continuas, etc.).

\newpage

Tabla comparativa de conceptos provenientes del algebra lineal


| Algebra lineal | Nombres alternativos
| ------------   | ------------- 
| Transformaciones lineales	  | Operadores lineales
| Producto punto    | Producto interno
| Eigenvector   | Eigenfunción


: Conceptos del algebra lineal aplicados a funciones

Las funciones también se pueden *transformar*. Por ejemplo, al derivar una función, se obtiene una función diferente. Observe la siguiente analogía:


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

## Eigenvector y Eigenfunción