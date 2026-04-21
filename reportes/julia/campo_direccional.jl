using Plots

# malla
x = -5:1:5
y = -5:1:5

# crear grid

X = [xi for yi in y, xi in x]
Y = [yi for yi in y, xi in x]


# campo direccional
U = ones(size(X))      # dx = 1
V = 0.2 .* X .* Y      # dy = f(x,y)

# normalizar (opcional, para que todas las flechas tengan tamaño similar)
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


