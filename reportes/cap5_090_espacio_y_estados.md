## Espacio y estados (control moderno)


La regla de las variables de estado (o de salida) para integradores en control y dinámica de sistemas establece que el número de integradores puros en un sistema es igual al número de variables de estado necesarias para describirlo completamente, lo cual equivale al orden de la ecuación diferencial del sistema.



\newpage

### Ejercicio


Encuentre la representacion en espacio de estados del siguiente sistema:


```{=latex}
\begin{equation}
\begin{aligned}
\frac{Y(s)}{U(s)} = \frac{(s+1)(s+2)}{(s-1)(s-2)}
\end{aligned}
\end{equation}
```

Una de varias alternativas de solución sería
separar la ecuacion de esta manera:



```{=latex}
\begin{equation}
\begin{aligned}
\frac{Y(s)}{U(s)} = G_1(s) G_2(s) = \frac{(s+1)}{(s-1)} \cdot \frac{(s+2)}{(s-2)}
\end{aligned}
\end{equation}
```


\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 8cm 0cm 5cm,clip]{./img/espacio_edos00.pdf}
\caption{Alternativamente en bloques}
\label{fig:ejercicio_espedos0}
\end{figure}


Para $G_1$ y/o $G_2$ y utilizando variable auxiliar $W(s)$, se puede estudiar un caso general así:

```{=latex}
\begin{equation}
\begin{aligned}
G_1(s) = \frac{Y(s)}{U(s)} = \frac{(s+a)}{(s+b)} \cdot  \frac{W(s)}{W(s)}
\end{aligned}
\end{equation}
```

Aplicando transformada inversa al numerador a fin de obtener $y(t)$: 

```{=latex}
\begin{equation}
\begin{aligned}
\mathcal{L}^{-1}\{Y(s)\} = \mathcal{L}^{-1}\{sW(s)+aW(s)\} = \boxed{y(t) = \dot{w}+aw(t)}
\end{aligned}
\label{eq:eqprim}
\end{equation}
```

Para el denominador $U(s)$:

```{=latex}
\begin{equation}
\begin{aligned}
\mathcal{L}^{-1}\{U(s)\} = \mathcal{L}^{-1}\{sW(s)+bW(s)\} = u(t) = \dot{w}+b
\end{aligned}
\end{equation}
```

O bien:

```{=latex}
\begin{equation}
\begin{aligned}
\boxed{\dot{w} = u(t)-bw(t)}
\end{aligned}
\label{eq:eqsec}
\end{equation}
```

Sustitutendo \ref{eq:eqsec} en  \ref{eq:eqprim} 



```{=latex}
\begin{equation}
\begin{aligned}
y(t) = u(t) + (a-b)w(t)
\end{aligned}
\label{eq:eqthird}
\end{equation}
```

En bloques: 

\begin{figure}[H]
\centering
\includegraphics[width=0.95\textwidth,trim=0cm 7cm 0cm 4cm,clip]{./img/ejer01_esp_edos.pdf}
\caption{Diagrama a bloques}
\label{fig:ss01}
\end{figure}



Retomando la ecuación original como 
producto de dos fracciones:



```{=latex}
\begin{equation}
\begin{aligned}
\frac{Y(s)}{U(s)} = \frac{(s+1)(s+2)}{(s-1)(s-2)} = \frac{(s+a_1)}{(s+b_1)} \cdot \frac{(s+a_2)}{(s+b_2)}
\end{aligned}
\end{equation}
```



\begin{figure}[H]
\centering
\includegraphics[width=0.97\textwidth,trim=0cm 7cm 0cm 4cm,clip]{./img/ejer01_1_esp_edos.pdf}
\caption{Concatenando dos entidades con $a_1=1$, $b_1=-1$, $a_2=2$, $b_2=-2$}
\label{fig:ss02}
\end{figure}


Sistema de ecuaciones resultante:

```{=latex}
\begin{equation}
\begin{aligned}
\dot{x_1} &= 2x_1 + 2x_2 + u \\
\dot{x_2} &= x_2 + u \\
y &= 2x_2 + u + 4x_1
\end{aligned}
\end{equation}
```




```{=latex}
\[
\begin{bmatrix}
\dot{x_1}\\
\dot{x_2}
\end{bmatrix}
=
\begin{bmatrix}
2 & 2\\
0 & 1
\end{bmatrix}
\begin{bmatrix}
x_1\\
x_2
\end{bmatrix}
+
\begin{bmatrix}
1\\
1
\end{bmatrix}u
\]
```





```{=latex}
\[
y = 
\begin{bmatrix}
4 & 2
\end{bmatrix}
\begin{bmatrix}
x_1\\
x_2
\end{bmatrix}
+
\begin{bmatrix}
1
\end{bmatrix}u
\]
```

El siguiente script *octave* sirve para recuperar la función de 
transferencia 


```matlab
pkg load control

A = [2  2;
    0  1];

B = [1;
     1];

C = [4 2];

D = 1;

sys = ss(A,B,C,D)
tf(sys)
```

Resultado:

```bash
Transfer function 'ans' from input 'u1' to output ...

      s^2 + 3 s + 2
 y1:  -------------
      s^2 - 3 s + 2

```
\newpage
