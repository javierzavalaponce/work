using ControlSystems, Plots

# Lugar Geometrico de las Raices
# (Root Locus)

s = tf("s")
R = 1000    # 1 KOhm
C = 100e-6  # 100 microfaradios

G = 1 / (R*C*s + 1)  

p = plot(rlocus(G),fontfamily="CMU Serif")
savefig(p, "root_locus.png")


#-------------------------------------

# Respuesta al escalon (5VDC, ejemplo)
t = 0:0.001:0.5
y, t_out = step(G, t)

y = vec(y)
y = 5 * y

plot(t_out, y,
     xlabel="Tiempo (s)",
     ylabel="Salida (V)",
     title="Respuesta al escalón",
     legend=false,
     fontfamily="CMU Serif"
     )

savefig("respuesta_escalon_5V.png")
