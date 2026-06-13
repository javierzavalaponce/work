using OrdinaryDiffEq
using Plots

function f!(dx, x, p, t)
    # referencia
    r = 5.0

    # ley de control
    u = r - x[1]

    # planta: ẋ = Ax + Bu
    dx[1] = 0*x[1] + 1*u
end

# Condición inicial: x(0) = 0.0
x0 = [0.0]
tspan = (0.0, 6.0)

prob = ODEProblem(f!, x0, tspan)
sol = solve(prob)

plot(sol, label=" ", xlabel="t", ylabel="x", title="dx/dt = (r - x), r=5")
savefig("integrador_retroalimentado.png")