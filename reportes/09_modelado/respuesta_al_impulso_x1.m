pkg load control

m_1 = 1;
m_2 = 1;
b_1 = 1;
b_2 = 1;
k = 1;

cns_2 = m_2;
cns_1 = b_1 + b_2;

cds_4 = m_1*m_2;
cds_3 = m_1*(b_1+b_2) + m_2*b_1;
cds_2 = k*m_2 + b_1*b_2;
cds_1 = k*(b_1+b_2);

num = [cns_2 cns_1 0];
den = [cds_4 cds_3 cds_2 cds_1 0];

G = tf(num, den)
figure
impulse(G)
grid on
title("Respuesta al impulso de x_1(t)")
xlabel("Tiempo [s]")
ylabel("x_1(t)")

print -dpng -r300 "impulse_x1.png"