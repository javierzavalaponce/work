using ForwardDiff
using LinearAlgebra  # para norm()

# Versión que acepta un vector [x, y]
function T(v)
    x, y = v[1], v[2]
    return 2*x^2 + 3*y^2 + x*y + 2*x + 5
end

# Punto de interés
punto = [1.0, -1.0]

# Calculamos el gradiente numérico en ese punto
grad_T = ForwardDiff.gradient(T, punto)

println("Gradiente en (1, -1): ", grad_T)
println("Magnitud del gradiente: ", norm(grad_T))

# Dirección de máximo crecimiento (normalizada)
dir_max_crecimiento = grad_T / norm(grad_T)
println("Dirección unitaria de máximo aumento: ", dir_max_crecimiento)

# Dirección opuesta (máximo descenso)
dir_max_descenso = -dir_max_crecimiento
println("Dirección unitaria de máximo descenso: ", dir_max_descenso)


