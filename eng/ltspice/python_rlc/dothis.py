#!/usr/bin/env python3

import sys
import pandas as pd
import matplotlib.pyplot as plt

filename = sys.argv[1] if len(sys.argv) > 1 else "prlc.csv"

# leer archivo separado por espacios y con header
df = pd.read_csv(filename, sep=r"\s+")

# usar nombres de columnas (porque ya tienes header: t v i)
t = df["t"]
y = df["v"]

plt.figure(figsize=(8,4))
plt.plot(t, y)

plt.xlabel("Tiempo (s)")
plt.ylabel("Voltaje (V)")
plt.title("V vs t")
plt.grid(True)

plt.tight_layout()
plt.savefig("grafica.png", dpi=150)
print("Guardado en grafica.png")


