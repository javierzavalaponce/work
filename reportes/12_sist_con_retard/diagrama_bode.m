pkg load control
% 1. Definir la función de transferencia G(s) = 10 / (s^2 + 3s + 10)
num = [10];
den = [1 3 10];
G = tf(num, den);

% 2. Graficar el diagrama de Bode
figure;
bode(G);
grid on;
title('Diagrama de Bode de G(s)');
pause



