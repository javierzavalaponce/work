pkg load control

A = [-3  1;
     -4  1];

B = [0;
     1];

C = [1 0];

D = 0;

sys = ss(A,B,C,D);

disp("Polos del sistema")
eig(A)

disp("Observabilidad")
Ob = obsv(A,C)
rank(Ob)

P = [-2 -6];

L = place(A',C',P)'

disp("Ganancia del observador")
L

disp("Polos del observador")
eig(A-L*C)



sys = ss(A-L*C,B,C,D)
tf(sys)

