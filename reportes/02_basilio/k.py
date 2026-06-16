import numpy as np
import matplotlib.pyplot as plt

s = np.linspace(-10, 10, 1000)

num = np.polyval([-1, 5, -6], s)
den = np.polyval([1, -1], s)

K = num / den

plt.plot(s, K)
plt.ylim(-20, 20)
plt.grid(True)
plt.show()

