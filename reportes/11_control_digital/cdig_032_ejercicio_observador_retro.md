```{=latex}
\clearpage
```

## Ejercicio, estabilizacion por retro de estados de observador

(esta sección requiere revisión)

El sistema dado es:
$$
G(s)=\frac{1}{(s-1)(s-2)}=\frac{1}{s^2-3s+2}
$$

Por lo tanto:
$$
\text{num}=[1], \qquad \text{den}=[1,\ -3,\ 2]
$$

$\texttt{tf2ss}$ devuelve la forma canónica controlable:

$$
A=\begin{bmatrix}3 & -2\\ 1 & 0\end{bmatrix},\qquad
B=\begin{bmatrix}1\\ 0\end{bmatrix},\qquad
C=\begin{bmatrix}0 & 1\end{bmatrix},\qquad
D=0
$$

Cuyos polos son efectivamente $s=1$ y $s=2$ (sistema inestable).

### Controlabilidad y observabilidad

$$\mathcal{C}=[B\ AB]=\begin{bmatrix}1 & 3\\ 0 & 1\end{bmatrix}$$

$\text{rank}(\mathcal{C})=2$. 
El sistema es completamente controlable.

**Observabilidad:**

$$
\mathcal{O}=\begin{bmatrix}C\\ CA\end{bmatrix}
=\begin{bmatrix}0 & 1\\ 1 & 0\end{bmatrix}
$$

$\text{rank}(\mathcal{O})=2$. 
El sistema es completamente observable.

Por lo tanto, sí es viable diseñar tanto el controlador por realimentación de estados como el observador de Luenberger.

### Diseño del controlador

Se busca que los polos del sistema realimentado estén en 
$\{-1,\ -2\}$. Con $\texttt{place(A, B, [-1 -2])}$ se obtiene $K$ tal que:

$$ \text{eig}(A-BK)=\{-1,\ -2\}$$

Esto es correcto.

### Diseño del observador

Se busca que los polos del observador estén en $\{-3,\ -4\}$. Para el observador, la dinámica del error es:
$$
\dot{e}=(A-LC)e
$$

Los polos del observador son los autovalores de $A-LC$. Para calcular $L$ usando $\texttt{place}$, se aprovecha la dualidad:
$$
\text{eig}(A-LC)=\text{eig}(A^T-C^TL^T)
$$

Por lo tanto:

```octave
L = place(A', C', [-3 -4])';
```

### Sistema aumentado

El sistema aumentado es:

$$
A_{\text{aug}}=
\begin{bmatrix}
A-BK & BK\\
0 & A-LC
\end{bmatrix}
$$

Este es el sistema en lazo cerrado cuando se combina el controlador por realimentación de estados *usando los estados estimados* 
$$\hat{x}$$
en lugar de $x$. Es decir, la ley de control es:

$$u=-K\hat{x}$$

Sustituyendo en la dinámica del sistema:

$$
\dot{x}=Ax+Bu=Ax-BK\hat{x}
$$

Y como $\hat{x}=x-e$, se tiene:
$$
\dot{x}=Ax-BK(x-e)=(A-BK)x+BKe
$$

La dinámica del error es:
$$
\dot{e}=(A-LC)e
$$

Por lo tanto, el sistema aumentado en las variables $(x,\ e)$ es:



$$
\begin{bmatrix}\dot{x}\\ \dot{e}\end{bmatrix}
=
\begin{bmatrix}
A-BK & BK\\
0 & A-LC
\end{bmatrix}
\begin{bmatrix}x\\ e\end{bmatrix}
$$

Los autovalores de esta matriz son la unión de los autovalores de 

\(A-BK\) y \(A-LC\)}, es decir:
$$
\{-1,\ -2\}\cup\{-3,\ -4\}=\{-1,\ -2,\ -3,\ -4\}
$$

Esto confirma que el diseño cumple con lo solicitado: un sistema de 4 estados con 4 polos en \(\{-1,-2,-3,-4\}\).




$$
A_{\text{aug}}=
\begin{bmatrix}
A-BK & BK\\
0 & A-LC
\end{bmatrix}
$$

\newpage

```octave
pkg load control   % place() está en control, no en signal
pkg load signal

%% Sistema original
num = [1];
den = [1 -3 2];

[A, B, C, D] = tf2ss(num, den);

disp("Sistema:")
A
B
C
D

%% Controlabilidad
Co = [B A*B];
disp("Matriz de controlabilidad:")
Co
disp("Rango de controlabilidad:")
rank(Co)

%% Observabilidad
Ob = [C; C*A];
disp("Matriz de observabilidad:")
Ob
disp("Rango de observabilidad:")
rank(Ob)

%% Controlador: polos en {-1, -2}
K = place(A, B, [-1 -2]);
disp("Ganancia K:")
K

%% Observador: polos en {-3, -4}
L = place(A', C', [-3 -4])';   % <-- transponer
disp("Ganancia L:")
L

%% Dinamica del sistema controlado
Acl = A - B*K;
disp("A-BK:")
Acl
disp("Polos del sistema controlado:")
eig(Acl)

%% Dinamica del error del observador
Aobs = A - L*C;
disp("A-LC:")
Aobs
disp("Polos del observador:")
eig(Aobs)

%% Sistema aumentado
Aaug = [A-B*K, B*K;
        zeros(2), A-L*C];

disp("Matriz aumentada:")
Aaug

disp("Polos del sistema aumentado:")
eig(Aaug)

```