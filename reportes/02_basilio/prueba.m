pkg load control

s = tf('s');

G = (s-2)/((s+1)*(s+3));

PI = (s+4)/s;

L = PI*G;

rlocus(L)
grid on
pause
