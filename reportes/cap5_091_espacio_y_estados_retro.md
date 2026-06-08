```{=latex}
\clearpage
```

### Retroalimentacion estática y retroalimentación de estados

Partiendo de un sistema expresado en espacio de estados,

$\dot{x} = Ax + Bu$
\
$y = Cx + Du$
\

con: 

* $A$ Matriz de estado
* $B$ Matriz de entrada
* $C$ Matriz de salida
* $D$ Matriz de transmisión directa

La idea general consiste en realimentar información del sistema hacia la entrada para modificar su dinámica.
*Nota:* en muchos problemas introductorios se asume $D=0$..


#### Retroalimentación estática de la salida. 
\
\
Si la señal de entrada o  bien la ley de control es: 

```{=latex}
\[
u=-ky
\]
```

con $k$ escalar , reemplazamos $u$ en $\dot{x} = Ax + Bu$


```{=latex}
\[
\begin{aligned}
\dot{x}&=Ax + B(-k(Cx)) \\
\dot{x}&=(A-BkC)x
\end{aligned}
\]
```


Por lo tanto la matriz $A_{cl}$ de lazo cerrado es:

```{=latex}
\begin{equation}
\boxed{
A_{cl}=(A-BkC)x
}
\end{equation}
```

#### Retroalimentación de estados
\
\
Ahora, si se dispone de todas las variables de estado y se utiliza la ley de control:

```{=latex}
\[
u=-Kx
\]
```

donde $K$ es un vector de ganancias y $y=Cx$, la dinámica en lazo cerrado queda:


```{=latex}
\[
\begin{aligned}
\dot{x}&=Ax + B(-Kx) \\
\dot{x}&=(A-BK)x
\end{aligned}
\]
```


Por lo tanto la matriz $A_{cl}$ de lazo cerrado es:




```{=latex}
\begin{equation}
\boxed{
A_{cl}=(A-BK)x
}
\end{equation}
```

**Observación**

En ambos casos, la estabilidad del sistema en lazo cerrado se determina a partir de los autovalores de la matriz
$A_{cl}$. La diferencia fundamental radica en la información utilizada por el controlador:

En la retroalimentación estática de salida se emplea únicamente la salida $y$
En la retroalimentación de estados se emplea el vector completo de estados $x$

La retroalimentación de estados ofrece, en general, una mayor capacidad para modificar la dinámica del sistema, siempre que el sistema sea controlable.

### Controlabilidad

La pregunta es: ¿Siempre existe un vector $K$ capaz de mover los polos donde yo quiera?
La respuesta es: No. Sólo si el sistema es controlable.

Para

```{=latex}
\[
\dot{x}=Ax + Bu
\]
```

decimos que el sistema es controlable si podemos mover el estado desde cualquier condición inicial hasta cualquier estado final mediante una entrada adecuada, Recordemos que $A$ describe la dinámica y $B$ describe dónde puede actuar el actuador. Si un estado nunca recibe influencia de u, será difícil o imposible controlarlo


#### La matriz de controlabilidad
\
\
Kalman demostró que basta construir una matriz $M$ de controlabilidad asi:

```{=latex}
\[
M = [B \; AB \; A^{2}B \;  ... \; A^{n-1}B] \in \mathbb{R}^{n\times n}
\]
```

y verificar que el rango de la matriz $M$ es $n$ donde $n$ es el número de estados. Si se cumple que $rank(M)=n$ el sistema es completamente controlable.


**Ejemplo:** Determinar la observabilidad de 



```{=latex}
\[
\begin{bmatrix}
\dot{x_1}\\
\dot{x_2}
\end{bmatrix}
=
\begin{bmatrix}
1 & 1\\
-2 & -1
\end{bmatrix}
\begin{bmatrix}
x_1\\
x_2
\end{bmatrix}
+
\begin{bmatrix}
0\\
1
\end{bmatrix}u
\]
```



```{=latex}
\[
y = 
\begin{bmatrix}
1 & 0
\end{bmatrix}
\begin{bmatrix}
x_1\\
x_2
\end{bmatrix}
\]
```

dado que el producto de $AB$ de matrices es

```{=latex}
\[
\begin{bmatrix}
1 & 1\\
-2 & -1
\end{bmatrix}
\begin{bmatrix}
0\\
1
\end{bmatrix} =
\begin{bmatrix}
1\\
-1
\end{bmatrix}
\]
```

La matriz de controlabilidad $M = [B \; AB ]$ queda:

```{=latex}
\[
M =
\begin{bmatrix}
0 & 1\\
1 & -1
\end{bmatrix}
\]
```

Recordemos que la regla práctica para matrices de 2×2: si el determinante es diferente de $0$ entonces el rango es $2$.
En este caso el sistema si **es controlable** ya que $det(M)=-1$. Alternativamente, en octave, la funcion $rank$ nos ayuda con el cálculo del rango así:


```octave
octave:> A = [0  1; 1 -1];
octave:> rank(A)
ans = 2
```





