import numpy as np
import matplotlib.pyplot as plt

A = np.array([[2, 1],
              [1, 2]])

# grid de vectores
X, Y = np.meshgrid(np.linspace(-2,2,10), np.linspace(-2,2,10))

U = A[0,0]*X + A[0,1]*Y
V = A[1,0]*X + A[1,1]*Y


plt.figure(figsize=(6,6))
plt.quiver(X, Y, X, Y, color='gray', alpha=0.5, label="Original")
plt.quiver(X, Y, U, V, color='blue', label="Transformado")

# eigenvectors
eigvals, eigvecs = np.linalg.eig(A)

for i in range(2):
    v = eigvecs[:, i]
    plt.quiver(0, 0, v[0]*2, v[1]*2, angles='xy', scale_units='xy', scale=1)

plt.xlim(-3,3)
plt.ylim(-3,3)
plt.axhline(0)
plt.axvline(0)
plt.grid()
plt.title("Transformación lineal + Eigenvectors")
plt.show()



