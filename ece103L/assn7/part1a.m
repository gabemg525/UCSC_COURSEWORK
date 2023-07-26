m=[0.9,0.99];

R=10000;

C=133*10^(-9);

f=0:0.1:200;

w=2*pi*f;

H1=((1+m(1))*((2*i*w*R*C).^2+1))./((2*i*w*R*C).^2+4*(1-m(1))*i*w*R*C+1);

H2=((1+m(2))*((2*i*w*R*C).^2+1))./((2*i*w*R*C).^2+4*(1-m(2))*i*w*R*C+1);

figure

subplot(2,1,1)

plot(f,abs(H1))

title('Magnitude and phase for m=0.9')

xlabel('f')

ylabel('Magnitude')

subplot(2,1,2)

plot(f,angle(H1))

xlabel('f')

ylabel('Phase (rad)')

figure

subplot(2,1,1)

plot(f,abs(H2))

title('Magnitude and phase for m=0.99')

xlabel('f')

ylabel('Magnitude')

subplot(2,1,2)

plot(f,angle(H2))

xlabel('f')

ylabel('Phase (rad)')