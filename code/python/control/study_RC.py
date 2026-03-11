import numpy as np
import matplotlib.pyplot as plt
import control as ct

# RC = 0.1; s = tf('s'); H = 1/(1+RC*s)
RC = 0.1
num = [1]           # Numerador
den = [RC, 1]       #  RC*s + 1
sys = ct.tf(num, den)

# bode(H); grid on;
plt.figure(figsize=(10,8))
ct.bode_plot(sys, dB=True, Hz=False, deg=True, grid=True)
plt.show()

