import sys
import matplotlib.pyplot as plt

# archivo de entrada
filename = sys.argv[1]

# leer datos
data = []
with open(filename) as f:
    for line in f:
        line = line.strip()
        if line:
            data.append(float(line))

# generar eje X (numero de muestra)
x = range(len(data))

# graficar
plt.figure(figsize=(10,4))
plt.plot(x, data)
plt.xlabel("Sample")
plt.ylabel("Value")
plt.title("Serial ADC Data")
plt.grid(True)

plt.tight_layout()
plt.savefig("img.png", dpi=300)


