R1 = 100000;
R2 = R1;
C1 = 220e-9;
C2 = C1;

s = tf('s');

A = [ (-1*(R1+R2))/(C1*(R1^2)) 1/(C1*R1); 1/(C2*R2) -1/(C2*R2)]
B = [R2/(C1*(R1^2));0]
C = [0 1]
D = 0

[num den] = ss2tf(A,B,C,D);
G = tf(num,den)
step(G)

H = 4*2066/(s^2+136.4*s+5*2066)
figure
step(H)