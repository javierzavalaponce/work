```{=latex}
\clearpage
```

## Modelado de sistemas mecanicos

**9/Sep/2026**

\begin{figure}[H]
\centering
\includegraphics[width=0.6\textwidth,trim=0cm 3cm 0cm 3cm,clip]{../img/modelado_ejer_clase001.pdf}
\end{figure}


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

```{=latex}
\begin{equation}
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
\end{equation}
```


```{=latex}
\begin{equation}
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
\end{equation}
```

