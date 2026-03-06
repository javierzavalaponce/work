import numpy as np
import matplotlib.pyplot as plt

# Coeficientes: [x^3, x^2, x, constante]
coeficientes = [1, 0, -15, -4]

# Método 1: np.roots() - MÁS RÁPIDO (usa companion matrix)
ceros = np.roots(coeficientes)
print("Ceros con np.roots():")
for i, cero in enumerate(ceros):
    print(f"z{i+1} = {cero:.4f}")

# Método 2: np.polynomial.polynomial.polyroots() - MÁS PRECISO
print("\nCeros con polyroots():")
ceros_poly = np.polynomial.polynomial.polyroots(coeficientes)
for i, cero in enumerate(ceros_poly):
    print(f"z{i+1} = {cero:.4f}")

# Gráfica con ceros marcados
x = np.linspace(-5, 5, 1000)
y = np.polyval(coeficientes, x)

plt.figure(figsize=(10, 6))
plt.plot(x, y, 'g-', linewidth=2, label='P(x) = x³ - 15x - 4')
plt.plot(ceros.real, ceros.imag, 'ro', markersize=10, label='Ceros complejos')

# Ejes del plano complejo
plt.axhline(0, color='black', linewidth=1)
plt.axvline(0, color='red', linewidth=1)
plt.grid(True, alpha=0.3)
plt.xlabel('Parte Real')
plt.ylabel('Parte Imaginaria')
plt.title('Polinomio Cúbico y sus Ceros en Plano Complejo')
plt.legend()
plt.xlim(-5, 5)
plt.ylim(-50, 50)
plt.axis('equal')
plt.tight_layout()
plt.savefig("polinomio_ceros.png", dpi=300)

