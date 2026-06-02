pkg load control

A = [1  1;
     0 -3];

B = [0;
     1];

C = [1 0];

D = 0;

sys = ss(A,B,C,D)
tf(sys)

