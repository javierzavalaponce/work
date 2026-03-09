import pandas as pd
import matplotlib.pyplot as plt
import sys

inputfilename = sys.argv[1] #ej. file.txt

# Leer CSV (cambia 'datos.csv' por tu archivo; usa header=0 si tiene nombres)
df = pd.read_csv(inputfilename, header=None, names=['x', 'y'])  # o header=0

# Graficar: primera columna vs segunda
plt.figure(figsize=(10, 6))
plt.plot(df['x'], df['y'], 'b-', linewidth=2, label='Datos RC')
plt.xlabel('Tiempo (secs))')
plt.ylabel('Voltaje(salida))')
plt.title('Gráfico de CSV con Python/Pandas')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("from_python.png", dpi=300)



