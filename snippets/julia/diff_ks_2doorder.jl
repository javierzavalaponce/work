using ControlSystems
using Plots

s = tf("s")
G = tf([1], [1, 4, 1])

t = 0:0.001:5

# Respuestas
y_open, t_open = step(G, t)
y2, t1 = step(feedback(2*G, 1), t)
y2_5, t1 = step(feedback(2.5*G, 1), t)
y1, t1 = step(feedback(1*G, 1), t)
y10, t10 = step(feedback(10*G, 1), t)
y100, t100 = step(feedback(100*G, 1), t)

# Crear figura
p = plot(
    xlabel="Tiempo (s)",
    ylabel="Amplitud",
    title="Respuesta al escalón del sistema",
    grid=true,
    legend=:bottomright
)

# Añadir curvas
plot!(p, vec(t_open), vec(y_open),
    label="Lazo abierto",
    lw=2,
    color=:black
)

plot!(p, vec(t1), vec(y1),
    label="K = 1",
    lw=2,
    color=:blue
)


plot!(p, vec(t1), vec(y2),
    label="K = 2",
    lw=2,
    color=:magenta
)

plot!(p, vec(t1), vec(y2_5),
    label="K = 2.5",
    lw=2,
    color=:cyan
)


plot!(p, vec(t10), vec(y10),
    label="K = 10",
    lw=2,
    color=:red
)

plot!(p, vec(t100), vec(y100),
    label="K = 100",
    lw=2,
    color=:green
)

savefig(p, "step_overlap.png")

