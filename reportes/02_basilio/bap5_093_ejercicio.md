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

1. Obtener una realizacion de estado
2. Reubicar polos en el semiplano estable mediante retroalimentacion de estados de observador
3. Proponer un control PI a fin de que el sistema sea capaz de seguir referencias
4. Responder:
   * De que tamaño seria la matriz de estado $A$ del sistema resultante (Sistema + Observador + Control PI)


\begin{figure}[H]
\centering
\includegraphics[width=1.0\textwidth,trim=0cm 7cm 0cm 4cm,clip]{../img/ejer_observabilidad01.pdf}
\caption{Representacion del sistema en G(s) en bloques}
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
Comprobación (en *octave*: ejercicio.m):


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


#### Reubicación de polos mediante retroalimentación de estados del observador

Mediante la retroalimentación de estados, se decide
reubicar los polos en $s=-2$ y $s=-4$. Con lo cual se obtiene la siguiente función de transferencia

```{=latex}
\[
\frac{Y(s)}{U(s)}
=
\frac{1}{(s+2)(s+4)}
\]
```

Cuya ecuación caracteristica es: 

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

e igualando con 

```{=latex}
\[
s^2 + 6s + 8 = 0
\]
```


Se tiene que :


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

Comprobación: se calculan los valores propios de $A_F$
a fin de verificar que los polos quedan en $s=-2$ y $s=-4$ como previsto.

En octave:

\vspace{2cm}

```octave
pkg load control

A = [3 1;
     0 1];

B = [0;
     1];

F = [35 10];

A_F = A-B*F

eig(A_F)
sys = ss(A,B,C,D)
tf(sys)
```

\vspace{2cm}

Resultado

\vspace{2cm}


```bash
A_F =

    3    1
  -35   -9

ans =

  -2
  -4

```

#### Cálculo de Matriz de corrección de estimación del Observador


```{=latex}
\[
A_{L}=(A-BL)
\]
```



