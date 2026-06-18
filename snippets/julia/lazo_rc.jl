using ControlSystems, Plots

s = tf("s")
R = 1000    # 1 KOhm
C = 100e-6  # 100 microfaradios


G = 1 / (R*C*s + 1)  

p = plot(rlocus(G))
savefig(p, "root_locus.png")

