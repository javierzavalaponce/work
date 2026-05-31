```{=latex}
\clearpage
```

# Simulación de Sistemas Dinámicos Usando *julia* 


## Sistemas dinámicos lineales LTI

Un sistema lineal puede ser descrito por la siguiente relación
entrada-salida:

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 7cm 0cm 5cm,clip]{./img/control02.pdf}
\caption{Sistema Lineal}
\label{fig:control2}
\end{figure}

\begin{equation}
\begin{aligned}
x(t) = \int_0^t G(t,\tau)u(\tau)\, d\tau
\end{aligned}
\end{equation}

