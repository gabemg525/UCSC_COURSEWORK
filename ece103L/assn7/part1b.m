ecg_signal=load("ecg_signal.mat");
x=ecg_signal.ecg;
t=ecg_signal.t;
m=[0.8,0.9];
C=133*10^(-9);
R=10000;
N=length(x);
f= linspace(-250, 250, N);
w=2*pi*f;
H=((1+m(2))*((2*i*w*R*C).^2+1))./((2*i*w*R*C).^2+4*(1-m(2))*i*w*R*C+1);
X=fft(x);
Z=X'.*H;
z=ifft(Z);

subplot(4,1,1)
plot(t,x)
xlabel('t')
ylabel('x(t)')


subplot(4,1,2)
plot(f,X)
xlabel('f')
ylabel('X(f)')


subplot(4,1,3)
plot(f,Z)
xlabel('f')
ylabel('Z(f)')

subplot(4,1,4)
plot(t,z)
xlabel('z')
ylabel('z(t)')
