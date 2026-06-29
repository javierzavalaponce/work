# Cargar el toolkit de lógica difusa
pkg load fuzzy-logic-toolkit

% 1. Definir el dominio del discurso (x) y la función de membresía agregada (mf)
x = 0:0.1:20; % Vector de valores en el eje x

% Crear tres funciones de membresía trapezoidales
mf1 = trapmf(x, [0 2 8 12]);
mf2 = trapmf(x, [5 7 12 14]);
mf3 = trapmf(x, [12 13 18 19]);

% Agregar las funciones de membresía (simulando la salida de la inferencia)
mf = max(0.9*mf1, max(0.5*mf2, 0.1*mf3));

% 2. Calcular la salida defusificada usando diferentes métodos
xCentroid = defuzz(x, mf, 'centroid');
xBisector = defuzz(x, mf, 'bisector');
xMOM = defuzz(x, mf, 'mom');
xSOM = defuzz(x, mf, 'som');
xLOM = defuzz(x, mf, 'lom');

% 3. Mostrar los resultados
fprintf('Resultados de la defusificación:\n');
fprintf('Centroide: %.4f\n', xCentroid);
fprintf('Bisector: %.4f\n', xBisector);
fprintf('MOM: %.4f\n', xMOM);
fprintf('SOM: %.4f\n', xSOM);
fprintf('LOM: %.4f\n', xLOM);

% 4. Visualizar el conjunto difuso y los resultados
figure;
plot(x, mf, 'LineWidth', 2);
hold on;

% --- Líneas verticales usando plot (compatible con Octave) ---
plot([xCentroid xCentroid], [0 max(mf)], '--k', 'LineWidth', 1.5);
plot([xBisector xBisector], [0 max(mf)], ':k', 'LineWidth', 1.5);
plot([xMOM xMOM], [0 max(mf)], '-.k', 'LineWidth', 1.5);

legend('Conjunto Difuso', 'Centroid', 'Bisector', 'MOM');
title('Comparación de Métodos de Defusificación');
xlabel('x');
ylabel('Grado de Membresía (\mu)');
grid on;
hold off;

% --- Pausa para mantener la figura abierta ---
input('Presiona Enter para cerrar la figura...');