using ControlSystems
using Plots

s = tf("s")

G = tf([1], [1, 4, 1])

# polos
poles = pole(G)

println(poles)

# root locus
p = rlocusplot(
    G,
    xlabel = "Parte real",
    ylabel = "Parte imaginaria",
    title = "Root Locus - Sistema de segundo orden",
    legend = false
)

# coordenadas
x = real.(poles)
y = imag.(poles)

# anotaciones
for i in eachindex(poles)

    annotate!(
        p,
        x[i] + 0.15,
        y[i] + 0.10,
        text(
            "p$i = $(round(x[i], digits=2)) + $(round(y[i], digits=2))j",
            9,
            :bottom,  # Alinear la parte inferior del texto con el punto
            :left     # Alinear la parte izquierda del texto con el punto
        )
    )

end

savefig(p, "root_locus2do_orden.png")

display(p)