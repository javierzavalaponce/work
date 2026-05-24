using Plots
dt = 0.1
T  = 6.0
t = 0:dt:T

x = zeros(length(t))
u = 5.0 # referencia r = 5
x[1] = 0.0

for k in 1:length(t)-1
    dx = -x[k] + u
    x[k+1] = x[k] + dt*dx
end

p = plot(t,x, xlabel = "t", ylabel = "x(t)", label = " ")
savefig(p, "integrador_retroalimentado.png")