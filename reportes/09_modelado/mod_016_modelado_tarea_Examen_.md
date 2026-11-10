```{=latex}
\clearpage
```

## Tarea de examen. Simulacion de sistema mecanico

\begin{figure}[H]   
\centering
\includegraphics[width=0.81\textwidth,trim=0cm 9cm 0cm 9cm,clip]{../img/modelado_ejer_exam.pdf}
\end{figure}

Diagramas de Cuerpo Libre

```{=latex}
\begin{center}

\begin{minipage}{0.45\textwidth}
\centering
\textbf{Masa 1 (\(m_1\))}
\vspace{0.5cm}

\begin{tikzpicture}[>=stealth]

% Dirección positiva
\draw[->, thick, dashed] (-0.9,0.5) -- (0.9,0.5)
    node[midway, above] {$x_1>0$};

% Eje troncal
\draw[thick] (0,0) -- (0,-5.5);

% Fuerzas m1
\draw[->, thick] (0,-1) -- (1.5,-1)
    node[right] {$f_1$};

\draw[->, thick] (0,-1.7) -- (-1.5,-1.7)
    node[left] {$m_1\ddot{x}_1$};

\draw[->, thick] (0,-2.4) -- (-1.5,-2.4)
    node[left] {$k_1x_1$};

\draw[->, thick] (0,-3.1) -- (-1.5,-3.1)
    node[left] {$k(x_1-x_2)$};

\draw[->, thick] (0,-3.8) -- (-1.5,-3.8)
    node[left] {$B_1\dot{x}_1$};

\draw[->, thick] (0,-4.5) -- (-1.5,-4.5)
    node[left] {$B(\dot{x}_1-\dot{x}_2)$};

\node at (0,-6) {\textbf{\(m_1\)}};

\end{tikzpicture}

\end{minipage}
\hfill
\begin{minipage}{0.45\textwidth}
\centering
\textbf{Masa 2 (\(m_2\))}
\vspace{0.5cm}

\begin{tikzpicture}[>=stealth]

% Dirección positiva
\draw[->, thick, dashed] (-0.9,0.5) -- (0.9,0.5)
    node[midway, above] {$x_2>0$};

% Eje troncal
\draw[thick] (0,0) -- (0,-5.5);

% Fuerzas m2
\draw[->, thick] (0,-1) -- (-1.5,-1)
    node[left] {$f_2$}; % f2 apunta a la izquierda según el dibujo original

\draw[->, thick] (0,-1.7) -- (-1.5,-1.7)
    node[left] {$m_2\ddot{x}_2$};

\draw[->, thick] (0,-2.4) -- (1.5,-2.4)
    node[right] {$k(x_1-x_2)$};

\draw[->, thick] (0,-3.1) -- (1.5,-3.1)
    node[right] {$B(\dot{x}_1-\dot{x}_2)$};

\draw[->, thick] (0,-3.8) -- (-1.5,-3.8)
    node[left] {$k_2x_2$};

\draw[->, thick] (0,-4.5) -- (-1.5,-4.5)
    node[left] {$B_2\dot{x}_2$};

\node at (0,-6) {\textbf{\(m_2\)}};

\end{tikzpicture}

\end{minipage}

\end{center}
```

$$
\begin{aligned}
m_1 \ddot{x}_1 + (B_1 + B)\dot{x}_1 - B\dot{x}_2 + (k_1 + k)x_1 - kx_2 &= f_1 \\
m_2 \ddot{x}_2 - B\dot{x}_1 + (B_2 + B)\dot{x}_2 - kx_1 + (k_2 + k)x_2 &= -f_2
\end{aligned}
$$

\newpage
despejando aceleraciones:

$$
\ddot{x}_1 = \frac{1}{m_1} \left[ f_1 - (B_1 + B)\dot{x}_1 + B\dot{x}_2 - (k_1 + k)x_1 + kx_2 \right]
$$

$$
\ddot{x}_2 = \frac{1}{m_2} \left[ -f_2 + B\dot{x}_1 - (B_2 + B)\dot{x}_2 + kx_1 - (k_2 + k)x_2 \right]
$$

Las entradas son las fuerzas externas del sistema: $f_1$  $f_2$.


### Paso 1: Definir los parámetros y las entradas

$$
\begin{aligned}
m_1 &= 1 \\
m_2 &= 2 \\
B_1 &= 0.2 \\ 
B_2 &= 0.3 \\
B   &= 0.1 \\
k_1 &= 10 \\
k_2 &= 5 \\
k   &= 8 \\
\end{aligned}
$$

Entrada: impulso en $f_1$

### Paso 2: Expresar como sistema de "primer orden" 

```{=latex}
\begin{center}
\begin{minipage}{0.48\textwidth}
$$
\begin{aligned}
y_0 & = x_1 \quad   \\
y_1 & = \dot{x}_1  \\
y_2 & = x_2 \quad   \\
y_3 & = \dot{x}_2 
\end{aligned}
$$
\end{minipage}%
\hfill
\begin{minipage}{0.48\textwidth}
Derivando, tenemos:
$$
\begin{aligned}
\dot{y}_0 &= y_1 \\
\dot{y}_1 &= \ddot{x}_1 \\
\dot{y}_2 &= y_3 \\
\dot{y}_3 &= \ddot{x}_2
\end{aligned}
$$
\end{minipage}
\end{center}
```
\newpage

### Paso 3: Simulación numérica (xppaut)

xppaut:

```lisp
# ---- Parámetros físicos ----
par m1=1, m2=2
par B1=0.2, B2=0.3, B=0.1
par k1=10, k2=5, k=8

# ---- Entradas (fuerzas externas) ----
aux f1 = 50*(t<0.1)   # impulso rectangular sobre m1
aux f2 = 0            # sin excitación sobre m2

# ---- Estado: x=x1, y=x1', u=x2, v=x2' ----
x' = y
y' = ( f1 - (B1+B)*y + B*v - (k1+k)*x + k*u ) / m1

u' = v
v' = ( -f2 + B*y - (B2+B)*v + k*x - (k2+k)*u ) / m2

# ---- Condiciones iniciales ----
# impulso de entrada f1 : 50*(t<0.1)
init x=0, y=0, u=0, v=0

# ---- Ajustes de simulación ----
@ total=20, dt=0.01, meth=stiff
done
```
\newpage

### Paso 4: Visualización 

$x_1$

\begin{figure}[H]
\centering
\includegraphics[width=0.76\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/x1_exam.png}
\end{figure}

$x_2$

\begin{figure}[H]
\centering
\includegraphics[width=0.76\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/x2_exam.png}
\end{figure}

