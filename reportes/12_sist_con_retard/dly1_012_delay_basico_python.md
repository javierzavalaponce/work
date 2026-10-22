```{=latex}
\clearpage
```

## Sistema retardo digital primer aprox

El delay es un sistema con memoria. Las ecuaciones en diferencias son:

Salida:
$$
y_n=x_n+d_n
$$
Delay:
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

