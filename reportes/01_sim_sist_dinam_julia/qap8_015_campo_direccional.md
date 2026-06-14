```{=latex}
\clearpage
```

# Campo direccional

El campo direccional proporciona una idea de como seria la solución de una ecuación diferencial, dibuja muchas flechas donde cada flecha esta en un punto del plano y representa una pendiente.


Para dibujar el campo direccional, en cada punto del plano construimos un pequeño vector cuya inclinación coincide con la pendiente $f(x,y)$. Para construir un vector con esa pendiente, podemos pensar en un triángulo rectángulo: elegimos una base de longitud 1 y una altura igual a $f(x,y)$.


\begin{figure}[H]
\centering
\includegraphics[height=0.2\textheight,trim=0cm 2cm 0cm 15cm,clip]{../img/vectorquiver00.pdf}
\caption{Triangulo con altura y pendiente igual a la derivada}
\label{fig:triangulo}
\end{figure}

El campo direccional no usa la derivada como cociente de incrementos, sino como una instrucción de inclinación. El siguiente script en *julia* es para generar
la figura \ref{fig:campo_dir_tanq}, es decir: el campo direccional para la ecuación diferencial : $\dot{x} = 5 - x$


\newpage

```julia
using Plots

# eje horizontal: tiempo
t = 0:1:10

# eje vertical: estado x
x = 0:1:10

# grid
T = [ti for xi in x, ti in t]
X = [xi for xi in x, ti in t]

# dx/dt = 5 - x
U = ones(size(T))
V = 5 .- X

# normalizar
L = sqrt.(U.^2 .+ V.^2)

U = U ./ L
V = V ./ L

# escalar flechas
scale = 0.5
U = scale .* U
V = scale .* V

# gráfico base
p = quiver(
    T, X,
    quiver=(U, V),
    arrow=false,
    color=:black,
    linewidth=1,
    aspect_ratio=1,
    xlims=(0,7),
    ylims=(0,7),
    xlabel="t",
    ylabel="x",
    tickfontsize=14, # tamaño de números 
    guidefontsize=16, # tamaño de etiquetas x,y
    legend=false,
    grid=false
)

# remarcar ejes
hline!(p, [0],
    color=:black,
    linewidth=2,
    linestyle=:solid
)

vline!(p, [0],
    color=:black,
    linewidth=2,
    linestyle=:solid
)

# remarcar equilibrio x=5
hline!(p, [5],
    color=:red,
    linewidth=2,
    linestyle=:dash,
    label="equilibrio"
)

savefig(p, "campo_tanque.png")
display(p)
```
