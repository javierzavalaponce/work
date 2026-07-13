pkg load control

A = [3  1;
     0 -1];

B = [0;
     1];

C = [1 1];

D = 0;

sys = ss(A,B,C,D)
G = tf(sys)

figure;
rlocus(G);
grid on;
pause