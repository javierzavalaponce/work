pkg load control   % place() está en control, no en signal
pkg load signal

%% Sistema original
num = [1];
den = [1 -3 2];

[A, B, C, D] = tf2ss(num, den);

disp("Sistema:")
A
B
C
D

%% Controlabilidad
Co = [B A*B];
disp("Matriz de controlabilidad:")
Co
disp("Rango de controlabilidad:")
rank(Co)

%% Observabilidad
Ob = [C; C*A];
disp("Matriz de observabilidad:")
Ob
disp("Rango de observabilidad:")
rank(Ob)

%% Controlador: polos en {-1, -2}
K = place(A, B, [-1 -2]);
disp("Ganancia K:")
K

%% Observador: polos en {-3, -4}
L = place(A', C', [-3 -4])';   % <-- transponer
disp("Ganancia L:")
L

%% Dinamica del sistema controlado
Acl = A - B*K;
disp("A-BK:")
Acl
disp("Polos del sistema controlado:")
eig(Acl)

%% Dinamica del error del observador
Aobs = A - L*C;
disp("A-LC:")
Aobs
disp("Polos del observador:")
eig(Aobs)

%% Sistema aumentado
Aaug = [A-B*K, B*K;
        zeros(2), A-L*C];

disp("Matriz aumentada:")
Aaug

disp("Polos del sistema aumentado:")
eig(Aaug)

