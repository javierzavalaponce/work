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
