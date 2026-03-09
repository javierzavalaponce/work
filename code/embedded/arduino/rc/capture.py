import serial
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/ttyUSB0',115200)

x=[]
y=[]

for i in range(500):
    line=ser.readline().decode().strip()
    y.append(float(line))

plt.plot(y,color="green")
plt.title("Simulación Circuito RC en arduino")
plt.grid()
plt.tight_layout()
plt.savefig("file_arduino.png", dpi=300)

