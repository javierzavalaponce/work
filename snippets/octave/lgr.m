pkg load control

G = tf([1 2], [1 2 -3 0]);

rlocus(G)
grid on
title("LGR de G(s) = (s+2)/(s(s-1)(s+3))")
pause
