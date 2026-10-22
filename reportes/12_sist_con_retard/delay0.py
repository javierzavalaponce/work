import numpy as np
import matplotlib.pyplot as plt

N = 4
g = 0.5
x = np.zeros(20); x[0] = 1.0
buf = np.zeros(N)
y = np.zeros(20)
w = 0
for n in range(20):
    d = buf[w]
    buf[w] = x[n] + d * g
    y[n] = x[n] + d
    w = (w + 1) % N

# stem devuelve un StemContainer con .markerline, .stemlines, .baseline
sx = plt.stem(x)
sx.markerline.set_linewidth(2)
sx.stemlines.set_linewidth(2)
sx.markerline.set_label('x[n] (entrada)')

sy = plt.stem(y, linefmt='C1-', markerfmt='C1o')
sy.markerline.set_linewidth(2)
sy.stemlines.set_linewidth(2)
sy.markerline.set_label('y[n] (salida con eco)')

plt.legend()
plt.grid(True)
plt.xlabel('n (muestras)')
plt.ylabel('amplitud')
plt.title('Delay N=4, g=0.5 — entrada (azul) vs salida (naranja)')
plt.show()

