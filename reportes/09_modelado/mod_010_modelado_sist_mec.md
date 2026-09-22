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

\vspace{1.8cm}

Lugar Geométrico de las raíces: 

\begin{figure}[H]
    \centering
    \begin{minipage}{0.48\textwidth}
        \centering
        \includegraphics[width=\textwidth]{../img/modo_rlocusx1s.png}
        \caption{G1}
        \label{fig:img00001}
    \end{minipage}
    \hfill
    \begin{minipage}{0.48\textwidth}
        \centering
        \includegraphics[width=\textwidth]{../img/modo_rlocusx2s.png}
        \caption{G2}
        \label{fig:imagen2}
    \end{minipage}
\end{figure}


\newpage

```octave
pkg load control
m_1 = 1;
m_2 = 1;
b_1 = 1;
b_2 = 1;
k = 1;

cns_2 = m_2;
cns_1 = b_1 + b_2;
cds_4 = m_1*m_2;
cds_3 = m_1*(b_1+b_2) + m_2*b_1;
cds_2 = k*m_2 + b_1*b_2;
cds_1 = k*(b_1+b_2);

x2cns_1  = b_1
x2cds_4 = m_1*m_2
x2cds_3 = (m_1*(b_1+b_2)+m_2*b_1)
x2cds_2 = (k*m_2+b_1*b_2)
x2cds_1 = k*(b_1+b_2)

num = [cns_2 cns_1 0];
den = [cds_4 cds_3 cds_2 cds_1 0];
num2 = [x2cns_1 0];
den2 = [x2cds_4 x2cds_3 x2cds_2 x2cds_1 0];
G1 = tf(num, den)
G2 = tf(num2, den2)
t = 0:0.01:19;
[y1,t] = impulse(G1,t);
[y2,~] = impulse(G2,t);

figure
plot(t,y1,'b',t,y2,'r','LineWidth',1.5)
grid on
xlabel("Tiempo [s]")
ylabel("Respuesta")
title("Respuesta al impulso")
print -dpng -r300 "impulse_x1_x2.png"
```
\newpage

Respuesta temporal

```octave
              s^2 + 2 s        
 G1:  -------------------------
      s^4 + 3 s^3 + 2 s^2 + 2 s


                  s            
 G2  -------------------------
      s^4 + 3 s^3 + 2 s^2 + 2 s

```

\begin{figure}[H]
    \centering
    \begin{minipage}{0.48\textwidth}
        \centering
        \includegraphics[width=\textwidth]{../img/impulse_x1_x2.png}
        \caption{Respuesta al impulso x1(t), x2(t)}
        \label{fig:X_1_t}
    \end{minipage}
    \hfill
    \begin{minipage}{0.48\textwidth}
        \centering
        \includegraphics[width=\textwidth]{../img/dos_escalones_x1_x2.png}
        \caption{Respuesta al impulso con escalones}
        \label{fig:X_2_t}
    \end{minipage}
\end{figure}

Asi sobrepuse los escalones en $octave$

```octave
G1 = tf(num, den)
G2 = tf(num2, den2)

t = 0:0.01:20;
u = zeros(size(t));

u(t >= 2)    = 10;
u(t >= 2+0.1) = 0;

[y1, t_out] = lsim(G1, u, t);
[y2, ~] = lsim(G2, u, t);
```