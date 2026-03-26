import numpy as np

A = np.array([[3, 1],
              [1, 2]])

# eigenvalues y eigenvectors
eigvals, eigvecs = np.linalg.eig(A)

print("Eigenvalues:", eigvals)
print("Eigenvectors:\n", eigvecs)



