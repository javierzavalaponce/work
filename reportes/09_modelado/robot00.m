% Parámetros del robot
L1 = 0.5; L2 = 0.4; 

% Condiciones iniciales articulares (en radianes)
q = [2; 2]; 

% Ganancia de control
K = 5; 

% Tiempo de simulación
dt = 0.01;
t = 0:dt:5;
N = length(t);

% Prealocación de matrices para guardar los datos
X_hist     = zeros(2, N);  
Xd_hist    = zeros(2, N);  
q_hist     = zeros(2, N); % Guardamos los ángulos para la animación

% --- 1. BUCLE DE CÁLCULO DE CONTROL ---
for i = 1:N
    % Cinemática Directa (Posición actual)
    x = L1*cos(q(1)) + L2*cos(q(1) + q(2));
    y = L1*sin(q(1)) + L2*sin(q(1) + q(2));
    X = [x; y];

    % Trayectoria deseada (Círculo)
    Xd = [0.3 + 0.1*cos(t(i)); 0.3 + 0.1*sin(t(i))];
    Xd_dot = [-0.1*sin(t(i)); 0.1*cos(t(i))];

    % Error de posición
    error = Xd - X;

    % Guardar historial
    X_hist(:, i)  = X;
    Xd_hist(:, i) = Xd;
    q_hist(:, i)  = q;

    % Matriz Jacobiana
    J = [ -L1*sin(q(1))-L2*sin(q(1)+q(2)), -L2*sin(q(1)+q(2));
        L1*cos(q(1))+L2*cos(q(1)+q(2)),  L2*cos(q(1)+q(2)) ];

    % Ley de control cinemático
    q_dot = inv(J) * (Xd_dot + K * error);

    % Integración numérica
    q = q + q_dot * dt;
end

% =========================================================================
% --- 2. BUCLE DE ANIMACIÓN EN TIEMPO REAL ---
% =========================================================================

figure('Name', 'Animación del Robot Planar 2 GDLL', 'NumberTitle', 'off', 'Position', [100, 100, 700, 600]);
grid on; hold on; axis equal;
axis([-(L1+L2) (L1+L2) -(L1+L2) (L1+L2)]); % Límites dinámicos basados en los eslabones
xlabel('Posición X (m)'); ylabel('Posición Y (m)');
title('Seguimiento de Trayectoria con Control Cinemático');

% Dibujar la trayectoria completa de referencia en el fondo (línea tenue)
plot(Xd_hist(1,:), Xd_hist(2,:), 'r:', 'LineWidth', 1);

% Inicializar los objetos gráficos vacíos (se actualizarán en el bucle)
h_tray_real = plot(NaN, NaN, 'b-', 'LineWidth', 1.5);      % Trazo azul del efector final
h_tray_des  = plot(NaN, NaN, 'ro', 'MarkerFaceColor', 'r'); % Punto rojo de la referencia actual
h_robot     = plot(NaN, NaN, 'k-o', 'LineWidth', 3, 'MarkerSize', 8, 'MarkerFaceColor', 'g'); % Cuerpo del robot

% Factor de salto para acelerar la animación (ej: graficar cada 3 pasos)
paso_animacion = 3; 

for i = 1:paso_animacion:N
    % Recuperar ángulos de este instante de tiempo
    q_act = q_hist(:, i);

    % Calcular las posiciones de las articulaciones (Codos y Extremos)
    x0 = 0;                  y0 = 0;                  % Base fija del robot
    x1 = L1*cos(q_act(1));   y1 = L1*sin(q_act(1));   % Articulación 2 (Codo)
    x2 = x1 + L2*cos(q_act(1)+q_act(2));              % Efector final (Punta)
    y2 = y1 + L2*sin(q_act(1)+q_act(2));

    % Actualizar la estructura física del robot
    set(h_robot, 'XData', [x0, x1, x2], 'YData', [y0, y1, y2]);

    % Actualizar la posición del objetivo móvil (punto rojo)
    set(h_tray_des, 'XData', Xd_hist(1, i), 'YData', Xd_hist(2, i));

    % Actualizar la línea del camino que el robot ya recorrió (trazo azul)
    set(h_tray_real, 'XData', X_hist(1, 1:i), 'YData', X_hist(2, 1:i));

    % Forzar dibujo inmediato en la pantalla y pausar para simular tiempo real
    drawnow;
    pause(dt * paso_animacion); 
end



