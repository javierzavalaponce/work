using OrdinaryDiffEq
using Plots

function f!(dx, x, p, t)
    r = 5.0
    dx[1] = r - x[1]
end

# Condición inicial: x(0) = 0.0
x0 = [0.0]
tspan = (0.0, 6.0)

prob = ODEProblem(f!, x0, tspan)
sol = solve(prob)

plot(sol, label=" ", xlabel="t", ylabel="x", title="dx/dt = (r - x), r=5")
savefig("integrador_retroalimentado.png")