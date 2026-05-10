using ControlSystems
using Plots

# Función para dibujar asíntotas automáticamente
function plot_asymptotes!(plot_obj, poles, zeros)
    n = length(poles)
    m = length(zeros)
    n_minus_m = n - m
    
    if n_minus_m <= 0
        println("n ≤ m, no hay asíntotas infinitas")
        return
    end
    
    sigma_a = (sum(poles) - sum(zeros)) / n_minus_m
    angles = [ (2k + 1)*π/n_minus_m for k in 0:n_minus_m-1 ]
    
    t_range = range(-12, 12, length=100)
    
    for θ in angles
        x = sigma_a .+ t_range
        y = tan(θ) .* t_range
        mask = abs.(y) .< 15
        plot!(plot_obj, x[mask], y[mask], 
              linestyle = :dash, linecolor = :green, 
              linewidth = 1.2, label = "")
    end
    
    # Marcar el centroide
    scatter!(plot_obj, [sigma_a], [0], 
             marker = (:star, 6, :magenta), 
             label = "Centroide σ_a = $(round(sigma_a, digits=2))")
end

# ==========================================
# DEFINIR EL SISTEMA (CORREGIDO)
# ==========================================
zeros = Float64[]             # ← CAMBIADO: Vector vacío de Float64
poles_list = [1, -2, -3]      # Polos: 1, -2, -3
k = 1

G = zpk(zeros, poles_list, k)

# Crear el gráfico LGR
p = rlocusplot(
    G,
    xlabel = "Parte real",
    ylabel = "Parte imaginaria",
    title = "LGR con asíntotas",
    legend = true,
    grid = true
)

# Dibujar polos (X rojas)
scatter!(
    p,
    real.(poles(G)),
    imag.(poles(G)),
    marker = (:x, 8, :red),
    label = "Polos"
)

# Dibujar ceros (no hay, pero por si acaso)
if !isempty(zeros)
    scatter!(
        p,
        real.(zeros),
        imag.(zeros),
        marker = (:circle, 8, :blue),
        label = "Ceros"
    )
end

# Añadir las asíntotas
plot_asymptotes!(p, poles_list, zeros)

# Mostrar y guardar
display(p)
savefig(p, "lgr_polos_1_-2_-3.png")

println("✅ Gráfico guardado exitosamente!")