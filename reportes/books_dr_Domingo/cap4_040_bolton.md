```{=latex}
\clearpage
```
## Capitulo 4 . Transformada de Laplace

La transformada de Laplace es un método que transforma una ecuación diferencial
en una ecuación algebraica mas fácil de resolver.

### La *transformada* en matemáticas

Ejemplo sencillo de transformación es cuando la multiplicación se cambia por la adición
mediante la *transformación logarítmica*: si, por ejemplo: **$a=bc$**

Entonces:


```{=latex} 
\[
\begin{aligned}
\log(a) &= \log(bc) \\
\log(bc) &= \log(b) + \log(c) \\
\log(b) + \log(c) &= d \\
a &= \operatorname{antilog}(d)
\end{aligned}
\]
```

La Transformada de Laplace toma una función del tiempo $f(t)$
 y la convierte en otra función $F(s)$

* Entrada: una señal en el tiempo f(t).
* Salida: una representación en la variable compleja s.

Transforma ecuaciones diferenciales en ecuaciones algebraicas, que suelen ser mucho más fáciles de resolver.


```{=latex}   
\[
F(s) = \mathcal{L}\{f(t)\}
=
\int_{0}^{\infty}
f(t)e^{-st}\,dt
\]
```


#### Transformada de Laplace para una función escalón




### Teoremas de valor final y de valor inicial

