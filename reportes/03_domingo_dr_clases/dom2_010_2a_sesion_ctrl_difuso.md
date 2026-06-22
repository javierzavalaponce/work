```{=latex}
\clearpage
```

# Introducción al control difuso


Supongamos que se busca controlar temperatura de un recipiente regulando la flama y que la lectura de un sensor nos dice cual es la temperatura medida $T$.

Un operador humano rara vez razona en términos de ecuaciones diferenciales o funciones de transferencia. En cambio, suele describir el estado del proceso mediante conceptos lingüísticos como:
*la temperatura es baja*,
*la temperatura es adecuada*,
*la temperatura es alta*.
y toma decisiones basadas en reglas heurísticas derivadas de su experiencia.

## Conjunto difuso

Un controlador difuso es un mecanismo para convertir reglas heurísticas expresadas en lenguaje natural en una ley de control implementable.


### Variable lingüística

En *lógica difusa*, estos conceptos cualitativos se representan mediante conjuntos difusos.
Para la variable lingüística ***Temperatura*** podemos definir:

* $C_B$: temperatura baja

* $C_C$: temperatura correcta

* $C_A$: temperatura alta

### Función de membresía y universo del discurso

Cada uno de estos conjuntos difusos tiene asociada una función de membresía (o pertenencia),
por ejemplo para el **conjunto** $C_B$, tenemos la **función** $\mu_B(T)$. Para una cierta temperatura $T_i$:


```{=latex}
\[
\mu_B(T_i) = c
\]
```

donde

```{=latex}
\[
c \in [0,1]
\]
```

significa que la temperatura $T_i$ pertenece con valor $c$ al conjunto $C_B$.

	
***Ejemplo:*** Si para una temperatura medida de $65^\circ$, 
se obtiene

```{=latex}
\begin{equation}
\begin{aligned}
μ_B(65)&=0 \\
μ_C(65)&=0.4 \\
μ_A(65)&=0.7
\end{aligned}
\label{eq:fuzificacion}
\end{equation}
```

Entonces la temperatura puede considerarse ***simultáneamente*** "correcta" y "alta", aunque con distintos grados de pertenencia. Esta idea de pertenencia simultánea es la esencia de la lógica difusa.

A todo el conjunto de valores que potencialmente podría tener el sensor de temperatura se le conoce como ***universo del discurso***, o *rango del sensor*. Por ejemplo, si el sensor puede medir temperaturas entre 0 y 100$^\circ$, su universo $U_s=[0,100]$.

Finalmente, las funciones de membresia pueden ser entonces expresadas matemáticamente como una función $\mu(x)$

```{=latex}
\[
\mu: \mathbb{R} \rightarrow [0,1]
\]
```

\newpage

### Formas comunes de funciones de membresía

Existen diversas formas paramétricas para definir $\mu(x)$. Las más utilizadas en control difuso son:

#### Función triangular

Definida por dos parámetros $(a,m)$:
donde $c$ es el ancho de la base y $m$ la pendiente de la rama creciente

```{=latex}
\[
\mu_{\text{tri}}(x; a,b,c) = 
\begin{cases}
0, & x \leq a \\[4pt]
\dfrac{x-a}{b-a}, & a < x \leq b \\[4pt]
\dfrac{c-x}{c-b}, & b < x < c \\[4pt]
0, & x \geq c
\end{cases}
\]
```

#### Función trapezoidal
Definida por cuatro parámetros $(a, b, c, d)$:

```{=latex}
\[
\mu_{\text{trap}}(x; a,b,c,d) = 
\begin{cases}
0, & x \leq a \\[4pt]
\dfrac{x-a}{b-a}, & a < x < b \\[4pt]
1, & b \leq x \leq c \\[4pt]
\dfrac{d-x}{d-c}, & c < x < d \\[4pt]
0, & x \geq d
\end{cases}
\]
```

#### Función de campana de Gauss

Definida por el centro $c$ y el ancho $\sigma$:

```{=latex}
\[
\mu_{\text{gauss}}(x; c, \sigma) = \exp\left(-\frac{(x-c)^2}{2\sigma^2}\right)
\]
```

#### Función sigmoide (S-curva)

Definida por los parámetros $a$(pendiente) y $c$ (punto de inflexión):

```{=latex}
\[
\mu_{\text{sig}}(x; a, c) = \frac{1}{1 + e^{-a(x-c)}}
\]	
```


## Fuzzificación

Consiste en ***convertir una variable numérica en grados de pertenencia.***. Observe nuevamente las ecuaciones \ref{eq:fuzificacion} (para el caso de la variable 
*Temperatura*):

```{=latex}
\[
\begin{aligned}
μ_B(65)&=0 \\
μ_C(65)&=0.4 \\
μ_A(65)&=0.7
\end{aligned}
\]
```

La lógica difusa permite construir controladores utilizando reglas lingüísticas similares a las empleadas por un operador humano, evitando en muchos casos la necesidad de disponer de un modelo matemático preciso de la planta.

## Mapeo en Python

Para mapear en 
