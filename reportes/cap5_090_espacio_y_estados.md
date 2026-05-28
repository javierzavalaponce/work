## Espacio y estados (control moderno)

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


Para $G_1$ utilizando variable auxiliar $W(s)$:

```{=latex}
\begin{equation}
\begin{aligned}
G_1(s) = \frac{(s+1)}{(s-1)} \cdot  \frac{W(s)}{W(s)}
\end{aligned}
\end{equation}
```


Analogamente, para $G_2$ utilizando variable auxiliar $W(s)$:






\newpage
