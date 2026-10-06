```{=latex}
\clearpage
```

## Control cinemático 

\vspace{1.0cm}

La ***cinemática*** es la parte de la mecánica que se ocupa de describir *cómo se mueve un sistema y cómo se relacionan entre sí sus movimientos*, sin preguntarse todavía qué fuerzas o motores los producen. En robótica, esto significa relacionar, por ejemplo, los movimientos de las articulaciones —sus giros— con la posición y el movimiento del extremo del robot en el espacio. Así, la cinemática nos permite pasar de preguntas como 
*¿cuánto giran las articulaciones?* a 
*¿dónde está y cómo se mueve el extremo?*, 
y también hacer el camino inverso.

La cinemática directa transforma coordenadas articulares en coordenadas cartesianas.
El Jacobiano es una matriz que, cerca de una configuración del robot, traduce pequeños movimientos de las articulaciones en pequeños movimientos del extremo.


\vspace{1.5cm}
Recuerda (del cálculo):
$$
f(x+\Delta x)
\approx
f(x)+f'(x)\Delta x
$$
El Jacobiano es básicamente la versión de varias variables de esa idea.
En una variable:
$$
\Delta y \approx f'(x)\Delta x
$$
En varias variables:
$$
\begin{bmatrix}
\Delta x\\
\Delta y
\end{bmatrix}
\approx
J
\begin{bmatrix}
\Delta q_1\\
\Delta q_2
\end{bmatrix}
$$

\newpage

Partimos del robot planar de dos eslabones:

$$
q=
\begin{bmatrix}
q_1\\
q_2
\end{bmatrix}
$$

y la posición de la punta es:
$$
p=
\begin{bmatrix}
x\\
y
\end{bmatrix}
$$


\vspace{1.0cm}

\begin{figure}[H]
\centering
\includegraphics[width=0.36\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/robot_planar.png}
\end{figure}

\vspace{1.0cm}

El Jacobiano es una tabla de cuatro preguntas sobre cómo responden $x$ e $y$ cuando muevo $q_1$ o $q_2$.

$$
J=\begin{bmatrix}
\frac{\partial x}{\partial q_1} &
\frac{\partial x}{\partial q_2}\\
\frac{\partial y}{\partial q_1} &
\frac{\partial y}{\partial q_2}
\end{bmatrix}
$$

Para el caso de un robot planar de dos eslabones ($L_1$ y $L_2$)

$$
J =
\begin{bmatrix}
-L_1\sin(q_1)-L_2\sin(q_1+q_2)
&
-L_2\sin(q_1+q_2)
\\[6pt]
L_1\cos(q_1)+L_2\cos(q_1+q_2)
&
L_2\cos(q_1+q_2)
\end{bmatrix}
$$


$$
\begin{bmatrix}
\Delta x\\
\Delta y
\end{bmatrix}=
J
\begin{bmatrix}
\Delta q_1\\
\Delta q_2
\end{bmatrix}
$$


---
la ecuación matemática, es la ley de control cinemático:

$$
\dot q = J^{-1}
\left(
\dot X_d + K\,error
\right)
$$


El Jacobiano nos dice:
$$
\dot X = J\dot q
$$
donde:
$$
X=\begin{bmatrix}
x\\
y
\end{bmatrix}
$$

Por tanto:
$$
\dot X=
\begin{bmatrix}
\dot x\\
\dot y
\end{bmatrix}
$$

Esto significa: Si sé qué tan rápido se mueven las articulaciones, puedo saber qué tan rápido se mueve la punta.
Pero en control queremos lo contrario.
Queremos decir: "Quiero que la punta se mueva con esta velocidad. ¿Qué velocidades debo mandar a $q_1$ y $q_2$?"

Ahí aparece 

$J^{-1}$

Es decir, se parte de:
$$
\dot X=J\dot q
$$

Multiplicamos ambos lados por $J^{-1}$:
$$
J^{-1}\dot X=J^{-1}J\dot q
$$
Como:
$$
J^{-1}J=I
$$
queda:
$$
\boxed{
\dot q=J^{-1}\dot X
}
$$

¡Eso es fundamental!
El Jacobiano hace:
$$
\dot q \longrightarrow \dot X
$$
Su inversa hace:
$$
\dot X \longrightarrow \dot q
$$



\begin{figure}[H]
\centering
\includegraphics[width=0.98\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/trayectoria002gdl.png}
\end{figure}