```{=latex}
\clearpage
```
## Espacio y estados (control moderno)

En control y dinámica de sistemas, el número de integradores puros en un sistema es igual al número de variables de estado necesarias para describirlo completamente, lo cual equivale al orden de la ecuación diferencial del sistema.

### Sistema general

* Ecuación de estado: $\dot{x} = Ax + Bu$
* Ecuación de salida: $y = Cx + Du$

Las matrices $A$ y $B$  describen la dinámica del sistema. $C$ y $D$ describen como observamos la planta


En un motor, por ejemplo, la entrada es el voltaje $u$ y los estados podrían ser
el ángulo y la velocidad de la flecha


```{=latex}
\[
x=
\begin{bmatrix}
{\theta}\\
{w}
\end{bmatrix}
\]
```

La estabilidad "natural" del sistema depende inicialmente de A, mientras que C y D sólo empiezan a influir cuando cerramos el lazo de control usando las señales medidas.


Por ejemplo, considere el sistema: 


```{=latex}
\[
A=
\begin{bmatrix}
0 & -1\\
3 & 2
\end{bmatrix},
\qquad
B=
\begin{bmatrix}
0\\
1
\end{bmatrix},
\qquad
C=
\begin{bmatrix}
1 & 0
\end{bmatrix},
\qquad
D=0
\]
```

La ecuación de estado es: 

```{=latex}
\[
\dot{x}
=
\begin{bmatrix}
0 & -1\\
3 & 2
\end{bmatrix}
x
+
\begin{bmatrix}
0\\
1
\end{bmatrix}
u
\]

\newpage
```

y la de salida es: 
```{=latex}
\[
y=
\begin{bmatrix}
1 & 0
\end{bmatrix}
x
\]
```
La matriz $C$ indica que la salida observada corresponde únicamente al primer estado. En este ejemplo, si

```{=latex}
\[
x=
\begin{bmatrix}
x_1\\
x_2
\end{bmatrix}
\]
```

entonces

```{=latex}
\[
y=x_1
\]
```

Aunque el sistema posee dos estados internos, únicamente el primero está siendo medido directamente.
¿Cómo entonces se puede modificar el comportamiento del sistema? 

\begin{figure}[H]
\centering
\includegraphics[width=0.64\textwidth,trim=0cm 7cm 0cm 4cm,clip]{./img/control03.pdf}
\caption{Control proporcional aplicado al sistema}
\label{fig:control03}
\end{figure}

```{=latex}
\[
u=r-ky
\]
```

y como

```{=latex}
\[
y=Cx
\]
```

```{=latex}
\[
u=r-kCx
\]
```

El controlador (proporcional en este caso) no tiene acceso directo a los estados; únicamente puede actuar sobre lo que mide el *sensor*. 

\vspace{2cm}

### Función de transferencia a partir de las matrices $A$, $B$, $C$ y $D$

La representación en variables de estado describe la dinámica interna del sistema mediante los estados.
Sin embargo, antes los sistemas de control se analizaban mediante funciones de transferencia, las cuales relacionan directamente la entrada con la salida:

```{=latex}
\[
G(s)=\frac{Y(s)}{U(s)}
\]
```
¿Cómo obtener la función de transferencia a partir de las matrices $A$, $B$, $C$ y $D$    ?
Para ello se aplica la Transformada de Laplace a las ecuaciones de estado, suponiendo condiciones iniciales nulas.

```{=latex}
\[
\dot{x}=Ax+Bu
\]
```
Aplicando Transformada de Laplace:
```{=latex}
\[
sX(s)=AX(s)+BU(s)
\]
```

Agrupando términos ($I$ es la matriz Identidad):

```{=latex}
\[
(sI-A)X(s)=BU(s)
\]
```

\newpage

\hrulefill

*Parentesis: Notas de repaso de algebra lineal*

* En álgebra lineal, una matriz cuadrada $Q$ de orden $n$, se dice que es invertible, si existe otra matriz cuadrada de orden $n$, llamada matriz inversa de Q y denotada por $Q^{-1}$
tal que $Q \cdot Q^{-1}=I_n$

* La matriz adjunta de $Q$, $adj(Q)$ es igual a la matriz transpuesta de la matriz de cofatores de Q:
  $adj(Q)$ = $cof(Q^{-1})$ . Es decir, en otras palabras,  hay mas de un "nombre" para esta matriz. En este documento, se maneja: $adj(Q)$


* En resumen, 
$Q^{-1}$ es
la inversa de una matriz $Q$ y se calcula como: 

```{=latex}
\[
Q^{-1} = 
\begin{bmatrix} a & b \\ c & d \end{bmatrix}^{-1} = \frac{1}{\det(Q)} 
adj(Q)= \frac{1}{ad-bc} 
\begin{bmatrix} \,\,\, d & \!\! -b \\ -c & \, a \end{bmatrix}
\]
```

\hrulefill

\vspace{1cm}

Entonces retomando, si la matriz $(sI-A)$ es invertible. 

```{=latex}
\[
X(s)=(sI-A)^{-1}BU(s)
\]
```

Utilizando la ecuación de salida:

```{=latex}
\[
Y(s)=CX(s)+DU(s)
\]
```

Tenemos:

```{=latex}
\[
Y(s)=C(sI-A)^{-1}BU(s)+DU(s)
\]
```

O bien:

```{=latex}
\begin{equation}
\boxed{
\frac{Y(s)}{U(s)}
=
\left[
C(sI-A)^{-1}B+D
\right]
}
\label{eq:ft_a_partir_edos}
\end{equation}
```

\vspace{1cm}

* $A$ contiene la dinámica interna.
* $(sI-A)^{-1}$ contiene los modos naturales del sistema.
* $B$ indica cómo la entrada excita esos modos.
* $C$ indica qué parte de esos modos observamos.
* $D$ representa un camino directo entrada-salida.








---



Retomando el elemplo de la matriz $A$ 
se tiene:

```{=latex}
\[
A=
\begin{bmatrix}
0 & -1\\
3 & 2
\end{bmatrix}
\]
```



para calcular el determinante $det(sI-A)$

```{=latex}
\[
det(sI-A) = det
\begin{bmatrix}
s & 1\\
-3 & s-2
\end{bmatrix}
=s^2 -2s + 3
\]
```

Para obtener la función de transferencia completa no basta calcular el determinante.
Recordemos que el objetivo es, primero obtener la matriz inversa:

```{=latex}
\[
(sI-A)^{-1} = \frac{1}{det(sI-A)} \cdot adj(sI-A)
\]
```

Y segundo, obtener la función de transferencia, como se mosto 
en la ecuación \ref{eq:ft_a_partir_edos}



```{=latex}
\[
\frac{Y(s)}{U(s)}
=
\left[
C(sI-A)^{-1}B+D
\right]
\]
```


Por esta razón, el polinomio

```{=latex}
\[
\det(sI-A)
\]
```

recibe el nombre de polinomio característico del sistema.

Este polinomio $D(s)=s^2 -2s -3$ es de hecho, la ecuación caracteristica del sistema 
a partir de la cual se pueden estudiar los criterios como el de estabilidad.



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
\mathcal{L}^{-1}\{U(s)\} = \mathcal{L}^{-1}\{sW(s)+bW(s)\} = u(t) = \dot{w}+bw(t)
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
