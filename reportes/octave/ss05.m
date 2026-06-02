pkg load control

A = [2  2;
    0  1];

B = [1;
     1];

C = [4 2];

D = 1;

sys = ss(A,B,C,D)
tf(sys)

