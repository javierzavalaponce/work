using ControlSystems
using Plots

# =========================
# Parametros del sistema
# =========================

ζ  = 0.3        # factor de amortiguamiento
ωn = 5.0        # frecuencia natural

# Funcion de transferencia:
#        ωn^2
# -------------------
# s² + 2ζωn s + ωn²

s = tf("s")

G = ωn^2 / (s^2 + 2*ζ*ωn*s + ωn^2)

# =========================
# Respuesta al escalon
# =========================

t = 0:0.001:5

y, t = step(G, t)

y = vec(y)

# =========================
# Metricas
# =========================

# Sobretiro
Mp = maximum(y) - 1

# Tiempo pico
idx_peak = argmax(y)
Tp = t[idx_peak]

# Tiempo de establecimiento (2%)
upper = 1.02
lower = 0.98

Ts = nothing

for i in eachindex(y)
    if all(lower .<= y[i:end] .<= upper)
        global Ts = t[i]
        break
    end
end

# =========================
# Grafica
# =========================

p = plot(
    t,
    y,
    lw=1,
    xlabel="Tiempo (s)",
    ylabel="Amplitud",
    label="Respuesta al escalón",
    title=" ",
    legend = :bottomright,
    color = "#0072BD"
    )

# Valor final
hline!([1], linestyle=:dash, label="Valor final")

# Banda 2%
hline!([upper], linestyle=:dot, label="2%")
hline!([lower], linestyle=:dot, label="")

# Punto de sobretiro
scatter!(
    [Tp],
    [maximum(y)],
    label="Sobretiro",
    markersize=3,
)

annotate!(
    Tp,
    maximum(y),
    text("Mp ", 10, :bottom)
    #text("Mp = $(round(Mp*100,digits=1))%", 10, :bottom)
)

# Tiempo pico
vline!(
    [Tp],
    linestyle=:dashdot,
    label="Tp"
)

annotate!(
    Tp,
    0.2,
    text("Tp", 10)
    #text("Tp = $(round(Tp,digits=2)) s", 10)
)

# Tiempo de establecimiento
if Ts !== nothing
    vline!(
        [Ts],
        linestyle=:dash,
        label="Ts"
    )

    annotate!(
        Ts,
        0.5,
        text("Ts", 10)
        #text("Ts = $(round(Ts,digits=2)) s", 10)
    )
end

savefig(p, "segundo_orden.png")

display(p)