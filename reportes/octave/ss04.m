pkg load control

A = [0  1;
    -2  3];

B = [0;
     1];

C = [0 6];

D = 1;

sys = ss(A,B,C,D)
tf(sys)

