using ControlSystems, Plots

s = tf("s")

R = 1.0
C = 1.0

G = 1 / (R*C*s)

p = plot(rlocus(G))
plot!(title="Root Locus RC")

savefig(p, "rlocus.png")


