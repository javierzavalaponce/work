import numpy as np
import matplotlib.pyplot as plt

A = np.array([[2, 1],
              [1, 2]])

x = np.array([1, 0])  # vector inicial cualquiera

traj = [x]

for _ in range(20):
    x = A @ x
    traj.append(x)

traj = np.array(traj)

plt.plot(traj[:,0], traj[:,1], 'o-')
plt.axhline(0)
plt.axvline(0)
plt.grid()
plt.title("Evolución del vector")
plt.show()


