```{=latex}
\clearpage
```

## Retardo en python primer programa

El delay es un sistema con memoria.
La ecuación en diferencias (la forma más limpia de verlo)

El script python siguiente, implementa esto:
Salida:
$$
y_n=x_n+d_n
$$

$$
d_n=x_{n−N}+ g \cdot d_{n−N}
$$

El buffer circular es la implementación eficiente de $x_{n−N}$. 


\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 10cm 0cm 8cm,clip]{../img/diag_retardo_prg.pdf}
\caption{Diagrama delay con \(g \in [0,1]\) y buffer \(N=4\)}
\label{fig:delay000}
\end{figure}


\newpage 
```python
import numpy as np
import matplotlib.pyplot as plt

N = 4
g = 0.5
x = np.zeros(20); x[0] = 1.0
buf = np.zeros(N)
y = np.zeros(20)
w = 0
for n in range(20):
    d = buf[w]
    buf[w] = x[n] + d * g
    y[n] = x[n] + d
    w = (w + 1) % N

# stem devuelve un StemContainer con .markerline, .stemlines, .baseline
sx = plt.stem(x)
sx.markerline.set_linewidth(2)
sx.stemlines.set_linewidth(2)
sx.markerline.set_label('x[n] (entrada)')

sy = plt.stem(y, linefmt='C1-', markerfmt='C1o')
sy.markerline.set_linewidth(2)
sy.stemlines.set_linewidth(2)
sy.markerline.set_label('y[n] (salida con eco)')

plt.legend()
plt.grid(True)
plt.xlabel('n (muestras)')
plt.ylabel('amplitud')
plt.title('Delay N=4, g=0.5 — entrada (azul) vs salida (naranja)')
plt.show()
```


\begin{figure}[H]
\centering
\includegraphics[width=1.0\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/delay_0py.png}
\caption{ilustracion de delay}
\end{figure}



