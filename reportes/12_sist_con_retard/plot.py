#!/usr/bin/env python3
import sys
import numpy as np
import matplotlib.pyplot as plt

path = sys.argv[1]

t, y = [], []
n_ok = n_bad = 0

with open(path, "r", errors="ignore") as f:
    for line in f:
        s = line.strip()
        if not s or s.upper() == "START" or s.startswith("#"):
            continue
        parts = s.split(",")
        try:
            if len(parts) == 2:
                t.append(float(parts[0]))
                y.append(float(parts[1]))
            else:
                y.append(float(parts[0]))
            n_ok += 1
        except ValueError:
            n_bad += 1
            if n_bad <= 5:   # muestra las primeras 5 líneas problemáticas
                print(f"[aviso] no parseable: {s!r}")

y = np.array(y)
if len(y) == 0:
    sys.exit(f"ERROR: no se leyó ninguna muestra de {path} "
             f"(líneas ok={n_ok}, malas={n_bad})")

# Eje X: tiempo si existe, si no índice
if t:
    x = np.array(t) / 1000.0   # ms -> s
    xlabel = "Tiempo (s)"
else:
    x = np.arange(len(y))
    xlabel = "Índice de muestra"

print(f"Muestras: {len(y)}  |  min={y.min():.0f}  max={y.max():.0f}")
if t:
    print(f"Duración: {x[-1] - x[0]:.3f} s")

plt.figure(figsize=(12, 4.5))
plt.plot(x, y, linewidth=0.9)
plt.xlabel(xlabel)
plt.ylabel("Posición (cuentas)")
plt.title(f"{path}  ({len(y)} muestras)")
plt.grid(alpha=0.3)
plt.tight_layout()
plt.show()


