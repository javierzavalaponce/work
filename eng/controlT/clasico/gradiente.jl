f(x,y) = x^2+y^2
grad(x,y)=(2x,2y)

function simula(x,y)
    ε = 0.001
    best_change = -Inf
    best_dir = (0.0, 0.0)
    for θ in range(0, 2π, length=10000)
        # dirección unitaria
        d = (cos(θ), sin(θ))
    
        # moverse en esa dirección
        x2 = x + ε*d[1]
        y2 = y + ε*d[2]
    
        Δf = f(x2,y2) - f(x,y)
    
        if Δf > best_change
            best_change = Δf
            best_dir = d
        end
    end
    println(best_dir)
    println(best_change)
end





