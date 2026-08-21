```{=latex}
\clearpage
```
# Espacios de funciones

Las funciones pueden ser vistas, desde el punto de vista cualitativo,  
como *otro tipo* de vectores. Las funciones se pueden sumar
para generar otra función. Tambien se pueden *escalar*: $\xi \cdot f(x)$

También se pueden *transformar*. Por ejemplo, al derivar una función, se obtiene una función diferente. Observe la siguiente analogía:

```{=latex}
\[
\begin{aligned}
L(\vec{v}+ \xi \vec{w}) &= L(\vec{v}) + \xi L(\vec{w}) \\
\frac{d}{dx}(e^x+ \xi x^2) &= \frac{d}{dx}(e^x) + \xi \frac{d}{dx}(x^2)
\end{aligned}
\]
```

| Algebra lineal | Nombres alternativos
| ------------   | ------------- 
| Transformaciones lineales	  | Operadores lineales
| Producto punto    | Producto interno
| Eigenvector   | Eigenfunción


: Conceptos del algebra lineal aplicados a funciones

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