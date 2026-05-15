## Capitulo 2 Ecs. Diferenciales de 1er orden. Resumen

Es posible que una ecuación diferencial no tenga
soluciones y que una ecuación diferencial tenga una solución que con los
métodos existentes actuales no se puede determinar. [@zill]

Por ejemplo, antes de buscar solución, considere la ecuacion diferencial: $f(x,y) = dy/dx = 0.2xy$.
Vamos a dibujar su **campo direccional** 
a fin de lograr una idea de como seria la solución de la ec. diferencial. Un campo direccional dibuja muchas flechas donde:

* Cada flecha esta en un punto del plano y representa una pendiente

Para dibujar el campo direccional, en cada punto del plano construimos un pequeño vector cuya inclinación coincide con la pendiente $f(x,y)$.

Para construir un vector con esa pendiente, podemos pensar en un triángulo rectángulo: elegimos una base de longitud 1 y una altura igual a $f(x,y)$.


\begin{figure}[H]
\centering
\includegraphics[height=0.25\textheight,trim=0cm 2cm 0cm 15cm,clip]{./img/vectorquiver00.pdf}
\caption{Triangulo con altura y pendiente igual a la derivada}
\label{fig:triangulo}
\end{figure}

El campo direccional no usa la derivada como cociente de incrementos, sino como una instrucción de inclinación.


El siguiente codigo en *julia* es para visualizar el campo direccional para la ecuación 
diferencial.

\newpage

```julia
using Plots

# puntos x,y:
x = -5:1:5
y = -5:1:5

# crear grid
X = [xi for yi in y, xi in x]
Y = [yi for yi in y, xi in x]

# campo direccional
U = ones(size(X))      # 1
V = 0.2 .* X .* Y      # f(x,y)

# normalizar (opcional, para que todas 
# las flechas tengan tamaño similar)
L = sqrt.(U.^2 .+ V.^2)
U = U ./ L
V = V ./ L

scale = 0.4
U = scale .* U
V = scale .* V

# plot
p = quiver(
    X, Y,
    quiver=(U, V),
    arrow=false, 
    color=:black,
    linewidth=1,
    aspect_ratio=1,
    xlims=(-5,5),
    ylims=(-5,5),
    legend=false,
    grid=false
)
savefig(p,"campo.png")
```
\begin{figure}[h]
\centering
\includegraphics[height=0.5\textheight]{./img/campo.png}
\caption{Campo direccional para $dy/dx = 0.2xy$, en azul: una solución particular}
\end{figure}

\newpage

**Solucion numérica de $dy/dx = 0.2xy$ con Julia**

```julia
using DifferentialEquations
using Plots

function f!(du, u, p, x)
    du[1] = 0.2 * x * u[1]
end

u0 = [1.0] # y(0) = 1
xspan = (-5.0, 5.0)

prob = ODEProblem(f!, u0, xspan)
sol = solve(prob)

p=plot(sol, label="y")
savefig(p,"solucion.png")
```


\begin{figure}[h]
\centering
\includegraphics[height=0.4\textheight]{./img/solucion00.png}
\caption{Solucion numérica de $dy/dx = 0.2xy$}
\end{figure}

\newpage



