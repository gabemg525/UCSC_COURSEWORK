ecg_signal=load("ecg_signal.mat");
x=ecg_signal.ecg;
t=ecg_signal.t;
m=[0.8,0.9];
C=133*10^(-9);
R=10000;
N=length(x);
f= linspace(-250, 250, N);
w=2*pi*f;
H2=((1+m(2))*((2*i*w*R*C).^2+1))./((2*i*w*R*C).^2+4*(1-m(2))*i*w*R*C+1);
X=fft(x);
Z=X'.*H2;
z=ifft(Z);


Energyx(1)=0;
Energyz(1)=0;
for i=2:N
Energyx(i)=Energyx(i-1)+(X(i))^2;
Energyz(i)=Energyz(i-1)+(Z(i))^2;
end



subplot(2,1,1)
plot(f,abs(Energyx/N))
xlabel('f')
ylabel('Energy(X)')


subplot(2,1,2)
plot(f,abs(Energyz/N))
xlabel('f')
ylabel('Energy(Z)')

