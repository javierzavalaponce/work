pkg load control;

% 1. Definir la variable de Laplace 's'
s = tf('s');

% 2. Definir la función de transferencia (ej. G(s) = 10 / ((s+1)(s+2)))
G = 1500 / ((s + 1) * (s + 2));


% 2.5 Generar el diagrama de BODE
figure;
bode(G);
grid on;
title('Diagrama de Bode de G(s)');


% 3. Generar el diagrama de Nyquist
figure;
nyquist(G);
grid on;
title('Diagrama de Nyquist de G(s)');





pause