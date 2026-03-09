import serial
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/ttyUSB0',115200)

y=[]

for i in range(500):
    line=ser.readline().decode().strip()
    y.append(float(line))

plt.plot(y)
plt.title("Simulación Circuito RC en arduino")
plt.grid()
plt.tight_layout()
plt.savefig("file.png", dpi=300)

