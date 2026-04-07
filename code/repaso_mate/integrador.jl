# integrador.jl

# Definimos el bloque integrador
mutable struct Integrador
    x::Float64   # estado (salida actual)
    dt::Float64  # paso de tiempo
end

# Función que avanza un paso en el tiempo
function step!(int::Integrador, u::Float64)
    int.x = int.x + u * int.dt
    return int.x
end


