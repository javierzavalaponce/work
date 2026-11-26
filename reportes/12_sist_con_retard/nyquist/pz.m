pkg load control;

% 1. Definir la variable de Laplace 's'
s = tf('s');

% 2. Definir la función de transferencia (ej. G(s) = 10 / ((s+1)(s+2)))
G = 10*(s-2) / ((s + 1) * (s + 2));

% 3. Generar el diagrama de Nyquist
figure;
pzmap(G);
grid on;
title('Diagrama pz de G(s)');

figure;
pzmap(G+1);
grid on;
title('Diagrama pz de (1+G(s))');


figure;
nyquist(G);
title('nyquist')

pause

