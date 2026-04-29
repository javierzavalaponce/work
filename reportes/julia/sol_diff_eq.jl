using DifferentialEquations

function f!(du, u, p, x)
    du[1] = 0.2 * x * u[1]
end


u0 = [1.0]        # y(0) = 1
xspan = (-5.0, 5.0)


prob = ODEProblem(f!, u0, xspan)
sol = solve(prob)

using Plots
p=plot(sol, label="Solución numérica")
savefig(p,"sol.png")




