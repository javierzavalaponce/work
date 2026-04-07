# test_integrador.jl

include("integrador.jl")

# Crear integrador con condición inicial x(0) = 0
int = Integrador(0.0, 1.0)

println("Simulación:")

for k in 1:5
    u = 2.0  # entrada (derivada constante)
    y = step!(int, u)
    println("Paso $k -> x = $y")
end

