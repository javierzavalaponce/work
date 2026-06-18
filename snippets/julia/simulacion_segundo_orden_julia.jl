using OrdinaryDiffEq
using Plots

function f!(dx, x, p, t)

    dx[1] =  x[2]   # ẋ₁ = x₂
    dx[2] = -x[1]   # ẋ₂ = -x₁

end

# Condiciones iniciales:
# x₁(0)=1
# x₂(0)=0
x0 = [1.0, 0.0]

# Intervalo de simulación
tspan = (0.0, 20.0)

prob = ODEProblem(f!, x0, tspan)
sol = solve(prob)

plot(sol,
     xlabel = "t",
     ylabel = "Estados",
     label = ["x₁(t)" "x₂(t)"])

savefig("oscilador.png")