using ControlSystems
using Plots


zeros = [-5]
poles = [1, -2, -3 , -4]
k = 1

# Crear sistema en ZPK
G = zpk(zeros, poles, k)

# Ver la función de transferencia
println(G)

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

# posicion de los labels
label_pos = [
    (1.0, -0.3),
    (-2.0, -0.3),
    (-3.0, 0.4),
    (-1.0, -0.6)
]

#anotaciones
for i in eachindex(poles)

    lx, ly = label_pos[i]

    annotate!(
        p,
        lx,
        ly,
        text(
            "p$i = $(round(poles[i], digits=2))",
            9,
            :left,
            :bottom
        )
    )

end

savefig(p, "rlocus_3er_orden.png")

display(p)