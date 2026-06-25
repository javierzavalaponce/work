# Cargar el toolkit de lógica difusa
pkg load fuzzy-logic-toolkit

# Definir el dominio
x = 0:0.1:10;

# Crear funciones de membresía
y_tri  = trimf(x, [3 5 7]);      # Triangular
y_trap = trapmf(x, [2 4 6 8]);   # Trapezoidal
y_gauss = gaussmf(x, [1 5]);     # Gaussiana
y_sig = sigmf(x, [2 5]);         # Sigmoide

# Graficar
plot(x, y_tri, 'LineWidth', 2, ...
     x, y_trap, 'LineWidth', 2, ...
     x, y_gauss, 'LineWidth', 2, ...
     x, y_sig, 'LineWidth', 2)
legend('Triangular', 'Trapezoidal', 'Gaussiana', 'Sigmoide', 'Location', 'best')
title('Funciones de Membresía')
xlabel('x')
ylabel('μ(x)')
grid on

# Guardar la figura en PNG (con buena resolución)
print -dpng -r300 'funciones_membresia.png'

# Confirmar en consola
disp('Figura guardada como funciones_membresia.png')

# Mantener la ventana abierta
pause()