import serial
import sys

if len(sys.argv) < 2:
    print(f"Uso: python {sys.argv[0]} nombre_archivo.txt")
    sys.exit(1)

archivo_salida = sys.argv[1]

ser = serial.Serial('/dev/ttyUSB0', 115200)
data = []

for _ in range(150):
    raw = ser.readline()
    try:
        line = raw.decode('ascii').strip()
        data.append(float(line))
    except (UnicodeDecodeError, ValueError):
        print(f"Línea inválida: {raw}")

ser.close()

with open(archivo_salida, 'w') as f:
    for valor in data:
        f.write(f"{valor}\n")

print(f"Datos guardados en {archivo_salida}")

