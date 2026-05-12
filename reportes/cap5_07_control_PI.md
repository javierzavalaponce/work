### Control PI


\begin{figure}[H]
\centering
\includegraphics[height=0.32\textheight,trim=0cm 2cm 0cm 2cm,clip]{./img/pi_a_bloques.pdf}
\caption{Controlador PI}
\label{fig:pi_a_blokes}
\end{figure}

Formula del PI


```{=latex}
\begin{equation}
\begin{aligned}
u(t)=K_p e(t)+K_i \int e(t)\,dt
\end{aligned}
\end{equation}
```
Donde: 

\
$e(t)$: error 
\
$u(t)$: acción de control 
\
$k_p$ : constante proporcional. La parte $P$ responde al presente (reacción inmediata: *qué tan "agresivo" reacciona el sistema*)
\
$k_i$ : constante de integración. La parte $I$ responde al pasado acumulado. La integral funciona como memoria. Si el error dura mucho, aunque sea pequeño, la integral crece.


**Analogía física**: Al llenar un tanque.

* Parte P: *¿Qué tan lejos estoy del nivel deseado?”*

* Parte I:  *¿Cuánto tiempo llevo debajo del nivel correcto?*, Su efecto: 
            elimina error en estado estacionario para entradas escalón.


\
Alternativamente, en Laplace:

```{=latex}
\begin{equation}
\begin{aligned}
C(s)=k_p+\frac{k_i}{s} = \frac{k_p s + k_i}{s}
\end{aligned}
\end{equation}
```

O bien, con $k = k_p$ y $\alpha = (k_i/k_p)$


```{=latex}
\begin{equation}
\label{eq:controlador_pi}
\begin{aligned}
C(s)=\frac{k(s+\alpha)}{s}
\end{aligned}
\end{equation}
```


La ecuación \eqref{eq:controlador_pi} muestra que el controlador PI introduce un polo en el origen $s=0$
y también introduce un cero en $s = -k_i/k_p$






\newpage
 