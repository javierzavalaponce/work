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
             label = "Centroide σ_a = $sigma_a")
end




zeros = [-5]
poles_list = [1, -2, -3, -4]
k = 1

G = zpk(zeros, poles_list, k)

p = rlocusplot(
    G,
    xlabel = "Parte real",
    ylabel = "Parte imaginaria",
    title = "LGR",
    legend = false,
    grid = true
)

# =========================
# Polos y ceros (solo marcadores)
# =========================

scatter!(
    p,
    real.(poles(G)),
    imag.(poles(G)),
    marker = (:x, 8, :red),
    label = "Polos"
)

scatter!(
    p,
    real.(zeros),
    imag.(zeros),
    marker = (:circle, 8, :blue),
    label = "Ceros"
)

display(p)
savefig(p, "rlocus_matlab_style.png")

# ... (tu código original hasta rlocusplot)



# Llamar la función
plot_asymptotes!(p, poles_list, zeros)
