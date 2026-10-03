```{=latex}
\clearpage
```

## Modelado de sistemas mecanicos. Tarea Ej.5


\begin{figure}[H]
\centering
\includegraphics[width=0.73\textwidth,trim=0cm 11cm 0cm 10cm,clip]{../img/modelado_ejer_5_mecanicos.pdf}
\end{figure}

### Método de Profesor Marquez
...
```{=latex}
\begin{center}

\begin{minipage}{0.45\textwidth}
\centering

\begin{tikzpicture}[>=stealth]

% Dirección positiva
\draw[->, thick, dashed] (-0.9,0.5) -- (0.9,0.5)
    node[midway, above] {$x_1>0$};

% Eje troncal
\draw[thick] (0,0) -- (0,-4.8);

% Fuerzas m1
\draw[->, thick] (0,-1) -- (1,-1)
    node[right] {$F$};

\draw[->, thick] (0,-1.7) -- (-1,-1.7)
    node[left] {$m_1\ddot{x}_1$};

\draw[->, thick] (0,-2.4) -- (-1,-2.4)
    node[left] {$K_1x_1$};

\draw[->, thick] (0,-3.1) -- (-1,-3.1)
    node[left] {$K_2x_1$};

\draw[->, thick] (0,-3.1) -- (1,-3.1)
    node[right] {$K_2x_2$};

\draw[->, thick] (0,-3.8) -- (-1,-3.8)
    node[left] {$B_1\dot{x}_1$};

\draw[->, thick] (0,-3.8) -- (1,-3.8)
    node[right] {$B_1\dot{x}_2$};

\node at (0,-5.2) {$m_1$};

\end{tikzpicture}

\end{minipage}
\hfill
\begin{minipage}{0.45\textwidth}
\centering

\begin{tikzpicture}[>=stealth]

% Dirección positiva
\draw[->, thick, dashed] (-0.9,0.5) -- (0.9,0.5)
    node[midway, above] {$x_2>0$};

% Eje troncal
\draw[thick] (0,0) -- (0,-5.5);

% Fuerzas m2
\draw[->, thick] (0,-1) -- (1,-1)
    node[right] {$K_2x_1$};

\draw[->, thick] (0,-1.7) -- (1,-1.7)
    node[right] {$B_1\dot{x}_1$};

\draw[->, thick] (0,-2.4) -- (-1,-2.4)
    node[left] {$m_2\ddot{x}_2$};

\draw[->, thick] (0,-3.1) -- (-1,-3.1)
    node[left] {$K_2x_2$};

\draw[->, thick] (0,-3.8) -- (-1,-3.8)
    node[left] {$B_1\dot{x}_2$};

\draw[->, thick] (0,-4.5) -- (-1,-4.5)
    node[left] {$K_3x_2$};

\draw[->, thick] (0,-5.2) -- (-1,-5.2)
    node[left] {$B_2\dot{x}_2+B_3\dot{x}_2$};

\node at (0,-5.7) {$m_2$};

\end{tikzpicture}

\end{minipage}

\end{center}
```

Para m1 ($\sum F_{x_1}=m_1\ddot{x}_1$):
$$
F  = m_1\ddot{x_1} + K_1x_1 + K_2(x_1-x_2) + B_1 (\dot{x_1} - \dot{x_2}) 
$$

Para m2 ($\sum F_{x_2}=m_2\ddot{x_2}_1$):
$$
K_2(x_1-x_2) + B_1(\dot{x_1} - \dot{x_2})  =K_3x_2 + B_2\dot{x_2}+B_3\dot{x_2}+ m_2\ddot{x_2} $$

\newpage

## Expresando en texto el sistema
```bash
  ____  _     _                            __        _           
 / ___|(_)___| |_     _ __ ___   ___  ___ /_/_ _ __ (_) ___ ___  
 \___ \| / __| __|   | '_ ` _ \ / _ \/ __/ _` | '_ \| |/ __/ _ \ 
  ___) | \__ \ |_ _  | | | | | |  __/ (_| (_| | | | | | (_| (_) |
 |____/|_|___/\__(_) |_| |_| |_|\___|\___\__,_|_| |_|_|\___\___/ 
                                                                 
POSITIVE_DIRECTION: right

NODES:
  WALL_L
  m1
  m2
  WALL_R
  GROUND

ELEMENTS:
  K1: WALL_L <-> m1
  K2: m1 <-> m2
  B1: m1 <-> m2
  K3: m2 <-> WALL_R
  B2: m2 <-> WALL_R
  B3: m2 <-> GROUND

INPUTS:
  F(t): applied to m1, direction right

COORDINATES:
  x1(t): displacement of m1, positive right 
  x2(t): displacement of m1, positive right   
```





\newpage

### En dominio de Laplace

 ```{=latex}
\vspace{1.0cm}
``` 
Primera ecuación ($m_1$):

$$ F(s)= m_1s^2X_1+ B_1sX_1-B_1sX_2+ K_1X_1+K_2X_1-K_2X_2 $$

$$ F(s)= \left[ m_1s^2+B_1s+K_1+K_2 \right]X_1 - \left[ B_1s+K_2 \right]X_2 $$

```{=latex}
\vspace{1.5cm}
```

Segunda ecuación ($m_2$):

$$ 0= m_2s^2X_2+ (B_1+B_2+B_3)sX_2 -B_1sX_1 +(K_2+K_3)X_2-K_2X_1 $$

$$ 0= -\left(B_1s+K_2\right)X_1 + \left[ m_2s^2+(B_1+B_2+B_3)s+K_2+K_3 \right]X_2 $$

```{=latex}
\vspace{2.5cm}
```
\newpage

Definimos, para simplificar:

$$ A(s)=m_1s^2+B_1s+K_1+K_2 $$ $$ B(s)=B_1s+K_2 $$ $$ C(s)=m_2s^2+(B_1+B_2+B_3)s+K_2+K_3 $$

Entonces tenemos el sistema:

$$ \begin{bmatrix} A(s) & -B(s)\\ -B(s) & C(s) \end{bmatrix} \begin{bmatrix} X_1\\ X_2 \end{bmatrix} = \begin{bmatrix} F\\ 0 \end{bmatrix} $$

La matriz inversa tiene determinante:

$$ \Delta(s)=A(s)C(s)-B^2(s) $$

Por tanto:

$$
\boxed{\frac{X_1(s)}{F(s)}=\frac{C(s)}{A(s)C(s)-B^2(s)}}
\qquad\text{y}\qquad
\boxed{\frac{X_2(s)}{F(s)}=\frac{B(s)}{A(s)C(s)-B^2(s)}}
$$

\newpage
### En dominio del tiempo

Aquí vamos a obtener el mismo análisis que en la sección anterior, pero con expresiones en el dominio del tiempo.

Partimos del sistema obtenido en el dominio de Laplace:

$$
F(s)=
\left[m_1s^2+B_1s+K_1+K_2\right]X_1(s)-
\left[B_1s+K_2\right]X_2(s)
$$

$$
0=-\left[B_1s+K_2\right]X_1(s)+
\left[m_2s^2+(B_1+B_2+B_3)s+K_2+K_3\right]X_2(s)
$$

Aplicando la transformada inversa de Laplace y suponiendo condiciones iniciales cero:

$$
F(t)=
m_1\ddot{x}_1+
B_1\dot{x}_1-
B_1\dot{x}_2+
K_1x_1+
K_2x_1-
K_2x_2
$$

y

$$
0=m_2\ddot{x}_2+ (B_1+B_2+B_3)\dot{x}_2 -
B_1\dot{x}_1+
(K_2+K_3)x_2-
K_2x_1
$$

Podemos expresar ambas ecuaciones en forma matricial agrupando los términos correspondientes a las aceleraciones, velocidades y desplazamientos:

$$
\begin{bmatrix}
m_1 & 0\\
0 & m_2
\end{bmatrix}
\begin{bmatrix}
\ddot{x}_1\\
\ddot{x}_2
\end{bmatrix}+
\begin{bmatrix}
B_1 & -B_1\\
-B_1 & B_1+B_2+B_3
\end{bmatrix}
\begin{bmatrix}
\dot{x}_1\\
\dot{x}_2
\end{bmatrix}+
\begin{bmatrix}
K_1+K_2 & -K_2\\
-K_2 & K_2+K_3
\end{bmatrix}
\begin{bmatrix}
x_1\\
x_2
\end{bmatrix}=
\begin{bmatrix}
F(t)\\
0
\end{bmatrix}
$$

El sistema puede re-escribirse de forma compacta con:

$$
x=
\begin{bmatrix}
x_1\\
x_2
\end{bmatrix},
\qquad
u=F(t)
$$

$$
\boxed{
M\ddot{x}+B\dot{x}+Kx=Fu
}
$$

\newpage
Las matrices del sistema quedan:

$$
M=
\begin{bmatrix}
m_1 & 0\\
0 & m_2
\end{bmatrix}
$$

$$
B=
\begin{bmatrix}
B_1 & -B_1\\
-B_1 & B_1+B_2+B_3
\end{bmatrix}
$$

$$
K=
\begin{bmatrix}
K_1+K_2 & -K_2\\
-K_2 & K_2+K_3
\end{bmatrix}
$$

Finalmente, la entrada puede expresarse mediante el vector:

$$
F=
\begin{bmatrix}
1\\
0
\end{bmatrix}
$$

por lo que:

$$
M\ddot{x}+B\dot{x}+Kx=
\begin{bmatrix}
1\\
0
\end{bmatrix}F(t)
$$

Esta representación matricial permite pasar posteriormente a una representación en espacio de estados.

\newpage
### En espacio de estados

Partimos de la representación matricial obtenida anteriormente:

$$
M\ddot{x}+B\dot{x}+Kx=Fu
$$

donde:

$$
x=
\begin{bmatrix}
x_1\\
x_2
\end{bmatrix},
\qquad
u=F(t)
$$

$$
M=
\begin{bmatrix}
m_1 & 0\\
0 & m_2
\end{bmatrix}
$$

$$
B=
\begin{bmatrix}
B_1 & -B_1\\
-B_1 & B_1+B_2+B_3
\end{bmatrix}
$$

$$
K=
\begin{bmatrix}
K_1+K_2 & -K_2\\
-K_2 & K_2+K_3
\end{bmatrix}
$$

$$
F=
\begin{bmatrix}
1\\
0
\end{bmatrix}
$$

Para obtener una representación en espacio de estados necesitamos convertir las ecuaciones de segundo orden en un sistema de ecuaciones de primer orden.

 ```{=latex}
\vspace{1.0cm}
``` 

\begin{figure}[H]
\centering
\includegraphics[width=0.18\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/sun_fun.png}
\end{figure}


\newpage
Despejamos las aceleraciones:

$$
M\ddot{x}=Fu-B\dot{x}-Kx
$$

Multiplicando por $M^{-1}$:

$$
\boxed{
\ddot{x}
=
-M^{-1}Kx
-M^{-1}B\dot{x}
+M^{-1}Fu
}
$$

Definimos ahora el vector de estado como:

$$
z=
\begin{bmatrix}
x\\
\dot{x}
\end{bmatrix}
\qquad
z=
\begin{bmatrix}
x_1\\
x_2\\
\dot{x}_1\\
\dot{x}_2
\end{bmatrix}
\qquad
\dot{z}=
\begin{bmatrix}
\dot{x}\\
\ddot{x}
\end{bmatrix}
$$

Sustituyendo la expresión obtenida para $\ddot{x}$:

$$
\dot{z}=
\begin{bmatrix}
\dot{x}\\
-M^{-1}Kx-M^{-1}B\dot{x}+M^{-1}Fu
\end{bmatrix}
$$

Por lo tanto, podemos escribir:

$$
\dot{z}=Az+Bu
$$

donde:

$$
\boxed{
A=
\begin{bmatrix}
0 & I\\
-M^{-1}K & -M^{-1}B
\end{bmatrix}
}
$$

y:

$$
\boxed{
B=
\begin{bmatrix}
0\\
M^{-1}F
\end{bmatrix}
}
$$

\newpage
Para este sistema:

$$
M^{-1}=
\begin{bmatrix}
\dfrac{1}{m_1} & 0\\
0 & \dfrac{1}{m_2}
\end{bmatrix}
$$

Por lo tanto:

$$
M^{-1}K= \begin{bmatrix}
\dfrac{K_1+K_2}{m_1} & -\dfrac{K_2}{m_1}\\
-\dfrac{K_2}{m_2} & \dfrac{K_2+K_3}{m_2}
\end{bmatrix}
$$

y:

$$
M^{-1}B=
\begin{bmatrix}
\dfrac{B_1}{m_1} & -\dfrac{B_1}{m_1}\\
-\dfrac{B_1}{m_2} & \dfrac{B_1+B_2+B_3}{m_2}
\end{bmatrix}
$$

Entonces la matriz de estado queda:

$$
A=
\begin{bmatrix}
0 & 0 & 1 & 0\\
0 & 0 & 0 & 1\\
-\dfrac{K_1+K_2}{m_1} &
\dfrac{K_2}{m_1} &
-\dfrac{B_1}{m_1} &
\dfrac{B_1}{m_1}\\
\dfrac{K_2}{m_2} &
-\dfrac{K_2+K_3}{m_2} &
\dfrac{B_1}{m_2} &
-\dfrac{B_1+B_2+B_3}{m_2}
\end{bmatrix}
$$

Mientras que la matriz de entrada es:

$$
B=\begin{bmatrix}
0\\0\\
\dfrac{1}{m_1}\\
0\end{bmatrix}
$$

Si consideramos como salidas los desplazamientos $x_1$ y $x_2$, entonces:

$$
y=
\begin{bmatrix}
x_1\\
x_2
\end{bmatrix}
$$

y por tanto:

$$
y=Cz+Du
$$

con:

$$
C=
\begin{bmatrix}
1&0&0&0\\
0&1&0&0
\end{bmatrix}
\qquad
D=
\begin{bmatrix}
0\\
0
\end{bmatrix}
$$

De esta forma, el modelo mecánico queda completamente representado mediante:

$$
\boxed{
\begin{aligned}
\dot{z}&=Az+Bu\\
y&=Cz+Du
\end{aligned}
}
$$

donde el vector de estado contiene las posiciones y velocidades de las dos masas:

$$
z=
\begin{bmatrix}
x_1&
x_2&
\dot{x}_1&
\dot{x}_2
\end{bmatrix}^{T}
$$

\begin{figure}[H]
\centering
\includegraphics[width=0.36\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/velo00.png}
\end{figure}