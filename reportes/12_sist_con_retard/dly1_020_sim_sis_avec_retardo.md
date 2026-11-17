```{=latex}
\clearpage
```

## Simulando sistemas con retardo

\begin{figure}[H]
\centering
\includegraphics[height=0.45\textheight,trim=0cm 3cm 0cm 3cm,clip]{../img/primer_sist_con_retardo.pdf}
\end{figure}


### Con $G(s)=\frac{1}{s+1}$ y $H(s)=k$


La señal de error es
$$
E(s)=R(s)-e^{-\tau s}Y(s).
$$

La planta responde $Y(s)=G(s)H(s)E(s)$. Sustituyendo:

$$
Y(s)=G(s)H(s)\bigl(R(s)-e^{-\tau s}Y(s)\bigr).
$$

Despejando $Y(s)/R(s)$:
$$
\frac{Y(s)}{R(s)}=\frac{G(s)H(s)}{1+G(s)H(s)\,e^{-\tau s}}.
$$

Los polos del lazo cerrado son las raíces de
$$
\boxed{1+G(s)H(s)\,e^{-\tau s}=0.}
$$

Con $G(s)=\dfrac{1}{s+1}$ y $H(s)=k$:
$$
1+\frac{k}{s+1}e^{-\tau s}=0
\;\Longrightarrow\;
(s+1)+k\,e^{-\tau s}=0.
$$

**Cruce por el eje imaginario (frontera de estabilidad)**

Como $e^{-\tau s}$ no es racional, no se pueden calcular los polos
con álgebra cerrada. En su lugar, se busca \textbf{cuándo} un polo
cruza el eje imaginario, es decir, se sustituye $s=j\omega$:
$$
(j\omega+1)+k\,e^{-j\omega\tau}=0
\;\Longrightarrow\;
k\,e^{-j\omega\tau}=-(j\omega+1).
$$

Igualando \textbf{módulo} y \textbf{fase} por separado:

\textbf{Módulo:}
$$
k=\sqrt{\omega^2+1}
\;\Longrightarrow\;
\omega_c=\sqrt{k^2-1}.
$$

\textbf{Fase:}
$$
-\omega\tau=\pi+\arctan\omega+2\pi n.
$$
Tomando $n=-1$ (primer cruce, $\tau>0$ mínimo):
$$
\tau_c=\frac{\pi-\arctan\omega_c}{\omega_c}.
$$

\begin{itemize}
  \item $\tau<\tau_c$: sistema \textbf{estable} (todos los polos con $\mathrm{Re}(s)<0$).
  \item $\tau=\tau_c$: \textbf{marginal} (polos sobre el eje imaginario, oscilación sostenida a $\omega_c$).
  \item $\tau>\tau_c$: \textbf{inestable} (polos con $\mathrm{Re}(s)>0$, oscilación creciente).
\end{itemize}

Para $k=2$: $\omega_c=\sqrt{3}\approx1.732$ rad/s y
$\tau_c=\dfrac{\pi-\pi/3}{\sqrt{3}}=\dfrac{2\pi}{3\sqrt{3}}\approx1.21$ s.
Con $\tau=0.7$ s $<\tau_c$, el lazo es estable.

**Efecto de $k$ y $\tau$:**


Al aumentar $k$, $\omega_c=\sqrt{k^2-1}$ crece y $\tau_c$ decrece:
\textbf{más ganancia tolera menos retardo}. Con $k$ fijo, si $\tau>\tau_c$
el lazo se vuelve inestable.



\newpage

#### Ejemplo: módulo y fase para $(s+2)+k e^{-\tau s}=0$

\
Sustituyendo $s=j\omega$:
$$
(j\omega+2)+k\,e^{-j\omega\tau}=0
\;\Longrightarrow\;
k\,e^{-j\omega\tau}=-(j\omega+2).
$$

\textbf{Módulo:}
$$
k=\bigl|-(j\omega+2)\bigr|=\sqrt{\omega^2+4}
\;\Longrightarrow\;
\omega_c=\sqrt{k^2-4}.
$$

\textbf{Fase:} el signo menos aporta un giro de $\pi$, y el complejo
$(j\omega+2)$ aporta $\arctan(\omega/2)$. Por tanto:
$$
-\omega\tau=\pi+\arctan\!\left(\frac{\omega}{2}\right)+2\pi n.
$$
Tomando $n=-1$ (primer cruce, $\tau>0$ mínimo):
$$
\tau_c=\frac{\pi-\arctan(\omega_c/2)}{\omega_c}.
$$

#### Elección de $n$ en la ecuación de fase

\

La ecuación de fase
$$
-\omega\tau=\pi+\arctan\!\left(\frac{\omega}{2}\right)+2\pi n
$$
se despeja como
$$
\tau=-\frac{\pi+\arctan(\omega/2)+2\pi n}{\omega}.
$$
Como $\tau$ es un retardo físico, debe cumplir $\tau>0$. El lado
izquierdo $-\omega\tau$ es negativo (con $\omega>0$, $\tau>0$), y
$\pi+\arctan(\omega/2)>0$, así que el término $2\pi n$ debe restar
lo suficiente para volver negativo el numerador. Eso exige $n<0$.
El primer valor que da $\tau>0$ es $n=-1$:
$$
\tau_c=\frac{\pi-\arctan(\omega_c/2)}{\omega_c}.
$$
Los valores $n\ge 0$ dan $\tau<0$ (sin sentido físico) y $n\le -2$
dan cruces posteriores (retardos mayores).

\newpage
