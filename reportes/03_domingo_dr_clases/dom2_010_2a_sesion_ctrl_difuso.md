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
### Soporte y núcleo 

En lógica difusa, el ***núcleo*** (o core) de un conjunto difuso es el conjunto de todos los elementos del universo que pertenecen completamente a ese conjunto. Para el conjunto difuso $A$, matemáticamente:

```{=latex}
\[
\text{Núcleo}(A) = \{ x \in X \mid \mu_A(x) = 1 \}
\]
```

Es útil contrastar el núcleo con el ***soporte*** de un conjunto difuso, ya que son conceptos complementarios:

* Núcleo (Core): Elementos con $\mu_A(x)=1$ (pertenencia total).
* Soporte (Support): Elementos con $\mu_A(x)>0$ (pertenencia en cualquier grado, por mínimo que sea).

El núcleo es, lógicamente, un subconjunto del soporte.
.
\newpage

### Formas comunes de funciones de membresía

Existen diversas formas paramétricas para definir $\mu(x)$. Las más utilizadas en control difuso son:

#### Función triangular

Una función triangular isósceles con base sobre el eje $x$ y pico en $x_c=\frac{x_0+x_1}{2}$
Definida por dos parámetros $(x_0,x_1)$ donde $x_0$ y $x_1$ son extremos del *soporte* del conjunto difuso. El punto central $x_c$ y el semi-ancho $s$ del triángulo quedan:


```{=latex}
\[
x_c = \frac{(x_0 + x_1)}{2} \qquad , \qquad s = \frac{(x_1 - x_0)}{2}
\]
```

```{=latex}
\[
\mu_{\text{tri}}(x; x_0,x_1) = 
\begin{cases}
0, & x \leq x_0 \\[4pt]
\dfrac{x-x_0}{s}, & x_0 < x \leq x_c \\[4pt]
\dfrac{x_1-x}{s}, & x_c < x < x_1 \\[4pt]
0, & x \geq x_1
\end{cases}
\]
```


\begin{figure}[H]
\centering
\includegraphics[width=0.7	\textwidth]{../img/fz_triangular.png}
\caption{Función triangular}
\end{figure}



\newpage
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
\vspace{2cm}

\begin{figure}[H]
\centering
\includegraphics[width=0.7	\textwidth]{../img/fz_trapezoidal.png}
\caption{Función trapezoidal}
\end{figure}

\newpage
#### Función de campana de Gauss

Definida por el centro $c$ y el ancho $\sigma$:

```{=latex}
\[
\mu_{\text{gauss}}(x; c, \sigma) = \exp\left(-\frac{(x-c)^2}{2\sigma^2}\right)
\]
```
\newpage
#### Función sigmoide (S-curva)

Definida por los parámetros $a$(pendiente) y $c$ (punto de inflexión):

```{=latex}
\[
\mu_{\text{sig}}(x; a, c) = \frac{1}{1 + e^{-a(x-c)}}
\]	
```

\newpage
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
	
## Inferencia (Mamdani | Sugeno)
...