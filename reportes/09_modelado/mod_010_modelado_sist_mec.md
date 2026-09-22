```{=latex}
\clearpage
```

## Modelado de sistemas mecanicos

Graficar respuesta temporal de movimiento de mas masas $m_1$ y $m_2$

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 5cm 0cm 7cm,clip]{../img/modelado_ejer_clase001.pdf}
\end{figure}

Ecuaciones de equilibrio:

Para $m1$: 

```{=latex}
\begin{equation}
F - b_1 \dot{x_2} = m_1\ddot{x_1} + b_1 \dot{x_1} + kx_1
\label{eq:para_m1}
\end{equation}
```
Para $m2$: 

```{=latex}
\begin{equation}
m_2\ddot{x_2} + b_1 \dot{x_2} + b_2 \dot{x_2} = b_1 \dot{x_1}
\label{eq:para_m2}
\end{equation}
```

\newpage

Funciones de Transferencia

```{=latex}
\begin{equation}
G_1(s) = 
\label{eq:g1tf}
\end{equation}
```

```{=latex}
\[
\frac{X_1(s)}{F(s)}
=
\frac{
m_2s^2+(b_1+b_2)s
}{
m_1m_2s^4+
\left[m_1(b_1+b_2)+m_2b_1\right]s^3+
(km_2+b_1b_2)s^2+
k(b_1+b_2)s
}
\]
```


```{=latex}
\begin{equation}
G_2(s) = 
\label{eq:g2tf}
\end{equation}
```


```{=latex}
\[
\frac{X_2(s)}{F(s)}
=
\frac{
b_1s
}{
m_1m_2s^4+
\left[m_1(b_1+b_2)+m_2b_1\right]s^3+
(km_2+b_1b_2)s^2+
k(b_1+b_2)s
}
\]
```


Lugar Geométrico de las raíces: 
\begin{figure}[H]
    \centering
    \begin{minipage}{0.48\textwidth}
        \centering
        \includegraphics[width=\textwidth]{../img/modo_rlocusx1s.png}
        \caption{Primera imagen}
        \label{fig:Root Locus G_1}
    \end{minipage}
    \hfill
    \begin{minipage}{0.48\textwidth}
        \centering
        \includegraphics[width=\textwidth]{../img/modo_rlocusx2s.png}
        \caption{Segunda imagen}
        \label{fig:imagen2}
    \end{minipage}
\end{figure}