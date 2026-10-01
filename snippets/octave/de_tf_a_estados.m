pkg load signal
num = [1];
den = [1 -3 2];

[A, B, C, D] = tf2ss(num, den);

A
B
C
D


