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
              linewidth = 1.2, label = "")  # Label vacío para no saturar
    end
    
    # Marcar el centroide
    scatter!(plot_obj, [sigma_a], [0], 
             marker = (:star, 6, :magenta), 
             label = "Centroide en $(round(sigma_a, digits=2))")
end

# Definir el sistema
zeros = [-5]
poles_list = [1, -2, -3, -4]
k = 1

G = zpk(zeros, poles_list, k)

# Crear el gráfico SIN leyenda automática (control manual)
p = rlocusplot(
    G,
    xlabel = "Parte real",
    ylabel = "Parte imaginaria",
    title = "LGR",
    legend = true,          # ← Cambiado de false a true
    grid = true
)

# AÑADIR ASÍNTOTAS (antes de display y savefig)
plot_asymptotes!(p, poles_list, zeros)

# Mostrar y guardar (después de añadir todo)
display(p)
savefig(p, "rlocus_with_asymptotes.png")