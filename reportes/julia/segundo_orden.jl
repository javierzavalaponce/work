using ControlSystems
using Plots

s=tf("s")
G = tf([1], [1, 4, 1])
println(pole(G))
p = rlocusplot(G)
savefig(p, "root_locus2do_orden.png")

# Construye el sistema en lazo cerrado con realimentación unitaria.
# para diferentes k (3 y 5) :
println(pole(feedback(3*G, 1)))
println(pole(feedback(5*G, 1)))
y, t = step(feedback(5*G,1))
plot(t, vec(y))
savefig("step5.png")