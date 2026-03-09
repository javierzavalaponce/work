y = 0.0; #salida
x = 5.0; #entrada , aplica escalon de 5 Volts

RC = 0.1; # simula RC R 1K C 100u
Ts = 0.002; #Simula una muestra cada 2 ms 

for i in range(500):
    y = y + (Ts/RC)*(x - y);
    t = i*Ts #tiempo
    print(f"{t:.4f},{y:.4f}")

