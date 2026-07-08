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

```bash
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
Transfer function 'ans' from input 'u1' to output ...
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
