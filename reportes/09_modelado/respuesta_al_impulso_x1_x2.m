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


x2cns_1  = b_1

x2cds_4 = m_1*m_2
x2cds_3 = (m_1*(b_1+b_2)+m_2*b_1)
x2cds_2 = (k*m_2+b_1*b_2)
x2cds_1 = k*(b_1+b_2)

num = [cns_2 cns_1 0];
den = [cds_4 cds_3 cds_2 cds_1 0];

num2 = [x2cns_1 0];
den2 = [x2cds_4 x2cds_3 x2cds_2 x2cds_1 0];


G1 = tf(num, den)
G2 = tf(num2, den2)


t = 0:0.01:10;

[y1,t] = impulse(G1,t);
[y2,~] = impulse(G2,t);

figure

plot(t,y1,'b',t,y2,'r','LineWidth',1.5)

grid on
xlabel("Tiempo [s]")
ylabel("Respuesta")
title("Respuesta al impulso")

legend("x_1(t)","x_2(t)","location","northeast")

print -dpng -r300 "impulse_x1_x2.png"