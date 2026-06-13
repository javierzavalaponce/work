### root locus. 1 er orden


El root locus es una herramienta gráfica de análisis que muestra cómo se mueven los polos del sistema en lazo cerrado al variar una ganancia $K$, Tambien se llama LGR (Lugar geométrico de las raices) , aquí es útil **pedagógicamente** porque muestra que en el caso del RC:

* hay un solo polo,
* se desplaza sobre el eje real,
* mientras permanezca negativo el sistema sigue estable.

**Nota aclaratoria:** Aunque el RC pasivo no posee una ganancia $K$ explícita, modificar $R$ o $C$ altera la dinámica del sistema (ver figura \ref{fig:rc_a_bloques}).  En aplicaciones de audio, modificar $R$ o $C$ cambia la frecuencia de corte ($f_c$) del filtro y, por tanto, su respuesta espectral.

```{=latex}
\begin{equation}
\begin{aligned}
f_c = \frac{1}{2\pi RC}
\end{aligned}
\end{equation}
```

Código *julia* para visualizar el lugar geometrico del polo:

```julia
using ControlSystems, Plots

# Lugar Geometrico de las Raices
# (Root Locus)

s = tf("s")
R = 1000    # 1 KOhm
C = 100e-6  # 100 microfaradios

G = 1 / (R*C*s + 1)  

p = plot(rlocus(G))
savefig(p, "root_locus.png")
```
\begin{figure}[H]
\centering
\includegraphics[height=0.35\textheight]{../img/root_locus.png}
\caption{root locus del RC}
\end{figure}


\newpage

