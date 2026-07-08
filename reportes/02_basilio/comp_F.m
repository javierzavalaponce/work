A = [3 1;
     0 1];

B = [0;
     1];

F = [35 10];

A_F = A-B*F

sys = ss(A,B,C,D)
tf(sys)
eig(A_F)
