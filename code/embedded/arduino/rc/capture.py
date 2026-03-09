import serial
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/ttyACM0',115200)

x=[]
y=[]

for i in range(500):
    line=ser.readline().decode().strip()
    a,b=line.split(',')
    x.append(float(a))
    y.append(float(b))

plt.plot(y)
plt.title("Simulación Circuito RC en arduino")
plt.grid()
plt.tight_layout()
plt.savefig("file.png", dpi=300)

