using ControlSystems, Plots

s = tf("s")
G = 1 / (s^2 + 4s + 1)

p = plot(rlocus(G))
savefig(p, "rlocus.png")

