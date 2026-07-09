```{=latex}
\clearpage
```

### Ejercicio

Para el sistema expresado en función de transferencia:


```{=latex}
\[
G(s)=
\frac{Y(s)}{U(s)}
=
\frac{1}{(s-1)(s-3)}
\]
```

1. Realización de estado.
2. Diseño de la retroalimentación de estados (obtención de $F$).
3. Verificación de observabilidad.
4. Diseño del observador (obtención de $L$).
5. Diseño del PI.
6. Sistema completo.

\begin{figure}[H]
\centering
\includegraphics[width=1.0\textwidth,trim=0cm 7cm 0cm 4cm,clip]{../img/ejer_observabilidad01.pdf}
\caption{Representacion del sistema en G(s) en bloques. La base del Observador.}
\label{fig:sis_ejer_ex00}
\end{figure}

#### Realizacion de estado


```{=latex}
\[
\begin{aligned}
\dot{x}
&=
\begin{bmatrix}
3 & 1\\
0 & 1
\end{bmatrix}
x
+
\begin{bmatrix}
0\\
1
\end{bmatrix}
u   \\
y&=
\begin{bmatrix}
1 & 0
\end{bmatrix}
x
\end{aligned}
\]

```


\newpage
Comprobación (en *octave*: ejercicio.m) para recuperar la función de transferencia:


\vspace{2cm}

```octave
pkg load control

A = [3  1;
     0 1];

B = [0;
     1];

C = [1 0];

D = 0;

sys = ss(A,B,C,D)

tf(sys)
```

\vspace{2cm}

Resultado:

```bash
Transfer function :
            1      
 y1:  -------------
      s^2 - 4 s + 3
```

\newpage


#### Reubicación de polos mediante retroalimentación de estados del observador.

Mediante la retroalimentación de estados, se decide
reubicar los polos en $s=-2$ y $s=-4$ (Semiplano izquierdo, estable). Con lo cual se obtiene la siguiente ecuación caracteristica : 

```{=latex}
\[
s^2 + 6s + 8 = 0
\]
```

Lo que se busca es:


\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 1cm 0cm 1cm,clip]{../img/ejer_observabilidad02.pdf}
\caption{Retroalimentacion de estados del observador}
\label{fig:sis_ejer_ex01}
\end{figure}

Con: 
```{=latex}
\[
F=
\begin{bmatrix}
f_1 & f_2
\end{bmatrix}
\]
```
\newpage

La matriz $A_{F}$ de lazo cerrado para retroalimentación de estados del observador es:

```{=latex}
\[
A_{F}=(A-BF)
\]
```


```{=latex}
\[
A_{F}
=
\begin{bmatrix}
3 & 1\\
0 & 1
\end{bmatrix}
-
\begin{bmatrix}
0\\
1
\end{bmatrix}
\begin{bmatrix}
f_1 & f_2
\end{bmatrix}
=
\begin{bmatrix}
3 & 1\\
-f_1 & 1-f_2
\end{bmatrix}
\]
```

y, para encontrar los valores de $f_1$ y $f_2$:

```{=latex}
\[
det(sI-A_F) = 
\begin{bmatrix}
s-3 & 1\\
f_1 & s-1+f_2
\end{bmatrix}
\]
```

```{=latex}
\[
det(sI-A_F) = 
(s-3)(s-1+f_2)+f_1 =
s^2-s+sf_2-3s+3-3f_2+f_1
\]
```


Reagrupando:


```{=latex}
\[
det(sI-A_F) = 
s^2+(f_2-4)s+3-3f_2+f_1
\]
```

e igualando con esta *nueva* ecuación característica:

```{=latex}
\[
s^2 + 6s + 8 
\]
```


Se tiene que al igualar coeficientes:


```{=latex}
\[
\begin{aligned}
f_2-4&=6\\
3-3f_2+f_1&=8
\end{aligned}
\]
```

Finalmente:

```{=latex}
\[
\boxed{
\begin{aligned}
f_2&=10\\
f_1&=35
\end{aligned}
}
\]
```

\newpage

Comprobación. Se calculan los valores propios de $A_F$
a fin de verificar que los polos quedan en $s=-2$ y $s=-4$ como previsto.

En octave:

\vspace{1cm}

```octave
pkg load control

A = [3 1;
     0 1];

B = [0;
     1];

F = [35 10];

A_F = A-B*F

eig(A_F)

```

\vspace{1cm}

Resultado (*eig()* devuelve los valores propios)

\vspace{1cm}

```bash
  -2
  -4
```

\newpage

#### Cálculo de Matriz de corrección de estimación del Observador


Como criterio general, los polos del observador se eligen en el semiplano izquierdo y con una dinámica más rápida que la del sistema controlado, de modo que el error de estimación converja rápidamente a cero.

En este ejercicio, se seleccionan los polos del observador en
$s=-5$ y $s=-6$. Ecuación característica:


```{=latex}
\[
s^2-11s+30=0
\]
```


\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 1cm 0cm 1cm,clip]{../img/ejer_observabilidad03.pdf}
\caption{Inyección estática del error de salida}
\label{fig:sis_ejer_ex03}
\end{figure}


La matriz $A_L$ de lazo cerrado para retroalimentación de estados del observador es:

```{=latex}
\[
A_{L}=(A-LC)
\]
```


Con: 
```{=latex}
\[
L=
\begin{bmatrix}
g_1 \\
g_2
\end{bmatrix}
\]
```

```{=latex}
\[
A_L
=
\begin{bmatrix}
3 & 1\\
0 & 1
\end{bmatrix}
-
\begin{bmatrix}
g_1\\
g_2
\end{bmatrix}
\begin{bmatrix}
1 & 0
\end{bmatrix}
=
\begin{bmatrix}
3-g_1 & 1\\
-g_2 & 1
\end{bmatrix}
\]
```

para encontrar los valores de $g_1$ y $g_2$:

```{=latex}
\[
det(sI-A_L) = 
\begin{bmatrix}
s-3+g_1 & -1\\
g_2 & s-1
\end{bmatrix}
\]
```

```{=latex}
\[
det(sI-A_L) = 
(s-3+g_1)(s-1)+g_2 =
s^2 -s -3s + 3 + g_1s  - g_1 + g_2
\]
```

Reagrupando:


```{=latex}
\[
det(sI-A_L) = 
s^2 + (g_1-4)s + (3 - g_1 + g_2)
\]
```

igualando coeficientes con

```{=latex}
\[
s^2 + 11s + 30 
\]
```


Se tiene que al igualar coeficientes:


```{=latex}
\[
\begin{aligned}
g_1-4&=11\\
3-g_1+g_2&=30
\end{aligned}
\]
```

Finalmente:

```{=latex}
\[
\boxed{
\begin{aligned}
g_1&=15\\
g_2&=42
\end{aligned}
}
\]
```

O bien: 
```{=latex}
\[
L=
\begin{bmatrix}
15 \\
42
\end{bmatrix}
\]
```


\newpage

Comprobación:

```octave
pkg load control

A = [3 1;
     0 1];

C = [1 0];

L = [15;
     42];

Aobs = A - L*C

eig(Aobs)
```
