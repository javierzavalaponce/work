#!/usr/bin/env python3
import sys
import numpy as np
import matplotlib.pyplot as plt

# --- 1. argumento: ruta del log ---
if len(sys.argv) != 2:
    sys.exit("Uso: python plot.py <archivo.log>")
path = sys.argv[1]

# --- 2. acumuladores ---
t, y = [], []            # pares (tiempo, posicion) para graficar
eventos = []             # lineas "D: ..." encontradas (solo informativo)
n_bad = 0                # lineas que no se pudieron parsear

# --- 3. parser linea por linea ---
with open(path, "r", errors="ignore") as f:
    for line in f:
        s = line.strip()

        # 3a. ignorar vacias y la basura de START del monitor serie
        if not s or "START" in s.upper():
            continue

        # 3b. eventos: empiezan con "D:"
        if s.startswith("D:"):
            eventos.append(s)
            continue

        # 3c. datos: deben ser exactamente "t,y"
        parts = s.split(",")
        if len(parts) != 2:
            n_bad += 1
            if n_bad <= 5:
                print(f"[aviso] no parseable: {s!r}")
            continue

        try:
            t.append(float(parts[0]))
            y.append(float(parts[1]))
        except ValueError:
            n_bad += 1
            if n_bad <= 5:
                print(f"[aviso] no parseable: {s!r}")

# --- 4. comprobaciones antes de graficar ---
if len(y) == 0:
    sys.exit(f"ERROR: no se leyo ninguna muestra de {path} (malas={n_bad})")

assert len(t) == len(y), (
    f"t ({len(t)}) y y ({len(y)}) no coinciden: "
    f"el archivo mezcla formatos"
)

t = np.array(t)
y = np.array(y)

# --- 5. reporte en consola ---
print(f"Muestras: {len(y)}  |  min={y.min():.0f}  max={y.max():.0f}")
print(f"Duracion: {(t[-1] - t[0]) / 1000.0:.3f} s")
print(f"Eventos: {len(eventos)}")
for ev in eventos[:10]:          # muestra hasta 10 eventos
    print(f"  {ev}")
if len(eventos) > 10:
    print(f"  ... y {len(eventos) - 10} mas")

# --- 6. grafica ---
x = t / 1000.0                   # ms -> s
plt.figure(figsize=(12, 4.5))
plt.plot(x, y, linewidth=0.9)
plt.xlabel("Tiempo (s)")
plt.ylabel("Posicion (cuentas)")
plt.title(f"{path}  ({len(y)} muestras)")
plt.grid(alpha=0.3)
plt.tight_layout()
plt.show()


