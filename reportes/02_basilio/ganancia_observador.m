pkg load control

A = [-3  1;
      0  1];

B = [0;
     1];

C = [1 0];

D = 0;

sys = ss(A,B,C,D);
disp("Polos del sistema")
eig(A)


P = [-2 -6];

L = place(A',C',P)'



disp("Ganancia del observador")
L

eig(A-L*C)
     


sys = ss(A-L*C,B,C,D)
tf(sys)

