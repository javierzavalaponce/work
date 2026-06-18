using OrdinaryDiffEq
using Plots

function f!(dx, x, p, t)
    dx[1] = 1
end

# Condición inicial: x(0) = 0.0
x0 = [0.0]
tspan = (0.0, 6.0)

prob = ODEProblem(f!, x0, tspan)
sol = solve(prob)

plot(sol, label=" ", xlabel="t", ylabel="x", title="(dt/dt) =  1")
savefig("x_dot_equal_u.png")
