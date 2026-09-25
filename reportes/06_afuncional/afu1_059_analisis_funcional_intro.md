```{=latex}
\clearpage
```
# Análisis funcional

\vspace{2.5cm}

*Las no linealidades de un sistema no deben considerarse como el
"demonio" por los ingenieros de control; de hecho, deben ser introducidas
durante el diseño del sistema de control, intencionalmente, a fin de alcanzar el objetivo.*
[@jairath]


\begin{figure}[H]
\centering
\includegraphics[width=0.63\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/pendulum.png}
\end{figure}

\newpage
## La Integral como límite

## Introducción Fibonacci en Espacio Vectorial

La sucesion de Fibonacci es:

```{=latex}
\[
\underbrace{0,1}_{\text{0+1=1}} ,1, 2, \underbrace{3}_{\text{3=2+1}}, 5, 8, 13, \dots
\]
```

de enteros positivos que tieme la propiedad de que después de los dos primeros términos,
cada término es la suma de los dos precedentes.

Entonces la serie completa queda definida especificando:

```{=latex}
\[
\begin{aligned}
f_0 &= 0 \\
f_1 &= 1 \\
f_n &= f_{n-1}+f_{n-2}
\end{aligned}
\]
```

Si denotamos los términos de la serie de Fibonacci como [@poole]:

```{=latex}
\[
\mathbf{v}=[f_0,f_1,f_2 ,\dots)
\]
```

Podemos entonces generalizar una sucesión *tipo* Fibonacci como aquella en que
$x_0 ,x_1 \in \mathbb{R}$ y $x_n = x_{n-1} + x_{n-2}$ para $n \geq 2$

```{=latex}
\[
\mathbf{x}=[x_0,x_1,x_2 ,\dots)
\]
```

Por ejemplo 
```{=latex}
\[
[1, \sqrt{2},1 + \sqrt{2},1 + 2\sqrt{2},2+3\sqrt{2},\dots)
\]
```

Es una sucesión *tipo* Fibonacci


\newpage

## Funciones vistas como vectores

Las funciones pueden ser vistas, desde el punto de vista cualitativo,  
como *otro tipo* de vectores. Observe que las funciones se pueden 
*escalar* ($\xi \cdot f(x)$) o sumar ($f(x)+g(x)$)
para generar otras funciones.

Observe y reflexione sobre la siguiente analogía:

```{=latex}
\[
\begin{aligned}
L(\vec{v}+ \xi \vec{w}) &= L(\vec{v}) + \xi L(\vec{w}) \\
\frac{d}{dx}(e^x+ \xi x^2) &= \frac{d}{dx}(e^x) + \xi \frac{d}{dx}(x^2)
\end{aligned}
\]
```

La serie de Taylor aproxima una función $f(x)$ mediante un polinomio alrededor de un punto $a$:

```{=latex}
\[
f(x)\approx
f(a)
+f'(a)(x-a)
+\frac{f''(a)}{2!}(x-a)^2
+\frac{f^{(3)}(a)}{3!}(x-a)^3
+\cdots
\]
```
En general:
```{=latex}
\[
\boxed{
f(x)=
\sum_{n=0}^{\infty}
\frac{f^{(n)}(a)}{n!}(x-a)^n
}
\]
```
si la serie converge a $f(x)$.

Ejemplo clásico: $f(x)=e^x$

Como $e^x$ y todas sus derivadas son $e^x$, evaluadas en $a=0$:
```{=latex}
\[
f(0)=f'(0)=f''(0)=\cdots=1.
\]
```
Entonces:

```{=latex}
\[
\boxed{
e^x
=
1+x+\frac{x^2}{2!}+\frac{x^3}{3!}+\cdots
}
\]
```

```python
import numpy as np
import matplotlib.pyplot as plt
import math

# Dominio
x = np.linspace(-3, 3, 500)

# Función exacta
y_exacta = np.exp(x)

# Serie de Taylor de e^x
y_taylor = (
    1
    + x
    + x**2 / math.factorial(2)
    + x**3 / math.factorial(3)
)

# Gráfica
plt.figure(figsize=(8, 5))

plt.plot(x, y_exacta, label=r"$e^x$")
plt.plot(
    x,
    y_taylor,
    label=r"$1+x+\frac{x^2}{2!}+\frac{x^3}{3!}$"
)

plt.xlabel(r"$x$")
plt.ylabel(r"$f(x)$")
plt.title("Aproximación de Taylor de $e^x$")
plt.grid(True)
plt.legend()

# Guardar como PNG
plt.savefig("taylor_ex.png", dpi=300, bbox_inches="tight")

plt.show()

```

\begin{figure}[H]
\centering
\includegraphics[width=0.90\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/taylor_ex.png}
\end{figure}


\newpage
La idea es

```{=latex}
\[
\boxed{
f(x)\approx
a_0+a_1x+a_2x^2+\cdots+a_nx^n
}
\]
```
Observa que las funciones

```{=latex}
\[
1,\quad x,\quad x^2,\quad x^3,\ldots
\]
```
pueden verse como *vectores* de un espacio vectorial de funciones.

Por ejemplo, consideremos el espacio de polinomios de grado menor o igual que $2$:

```{=latex}
\[
P_2=
\left\{
a+bx+cx^2:\;a,b,c\in\mathbb{R}
\right\}.
\]
```

Este conjunto es un espacio vectorial y una base para él es

```{=latex}
\[
\mathcal{B}=\{1,x,x^2\}.
\]
```
Por tanto, cualquier polinomio $p(x)=a+bx+cx^2$
puede escribirse como una combinación lineal de los elementos de la base:
$p(x)=a(1)+b(x)+c(x^2)$

Sus coordenadas respecto de la base $\mathcal{B}$ son

```{=latex}
\[
[p]_{\mathcal B}
=
\begin{bmatrix}
a\\
b\\
c
\end{bmatrix}.
\]
```

La serie de Taylor utiliza exactamente esta idea. Una función puede
aproximarse mediante una combinación lineal de las funciones

```{=latex}
\[
1,\quad x,\quad x^2,\quad x^3,\ldots
\]
```
De manera general,

```{=latex}
\[
f(x)\approx
a_0(1)+a_1x+a_2x^2+\cdots+a_nx^n.
\]
```

Por ejemplo, para $f(x)=e^x$, alrededor de $x=0$:

```{=latex}
\[
e^x\approx
1+x+\frac{x^2}{2!}+\frac{x^3}{3!}.
\]
```
Esto puede escribirse como

```{=latex}
\[
e^x\approx
1(1)+1(x)+\frac{1}{2!}(x^2)+\frac{1}{3!}(x^3).
\]
```
Respecto de la base

```{=latex}
\[
\mathcal{B}=\{1,x,x^2,x^3\},
\]
```
el vector de coordenadas del polinomio de Taylor es

```{=latex}
\[
\boxed{
\begin{bmatrix}
1\\
1\\
\frac{1}{2!}\\
\frac{1}{3!}
\end{bmatrix}
}.
\]
```

Así, la idea fundamental puede resumirse como
```{=latex}
\[
\boxed{
\text{Taylor}
=
\text{aproximar una función mediante una combinación lineal de funciones base}
}
\]
```
Esto muestra que los espacios vectoriales no están limitados a vectores
geométricos de $\mathbb{R}^2$ o $\mathbb{R}^3$: también podemos construir
espacios vectoriales cuyos elementos sean funciones.

\newpage

### Base del espacio de funciones reales

Aquí hay que distinguir según el tipo de base:

