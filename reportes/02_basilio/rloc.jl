using ControlSystems
using Plots

s=tf("s")
G = tf([1, -1], [1, -5, 6])
println(pole(G))
p = rlocusplot(G)
savefig(p, "rlocus.png")