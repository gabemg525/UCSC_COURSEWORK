h1_0=dsolve('100*D2hz+20*Dhz+hz=0','hz(0)=0','Dhz(0)=1','t');
h2_0=dsolve('100*D2hz+0.2*Dhz+hz=0','hz(0)=0','Dhz(0)=1','t');
h1=diff(h1_0);

h2=diff(h2_0);
disp(['impulse response h(t) = (',char(h1),')u(t)']);
disp(['impulse response h(t) = (',char(h2),')u(t)']);

subplot(2,1,1)
to_plot1=@(t) (exp(-t/10) - (t*exp(-t/10))/10).*(t>=0);
fplot(to_plot1,[-10 300]);
axis ([-10 300 -1.0 1.2]);
xlabel ('t'); ylabel ('h1(t)');

subplot(2,1,2)
to_plot2=@(t) (exp(-t/1000)*cos((3*1111^(1/2)*t)/1000) - (1111^(1/2)*exp(-t/1000)*sin((3*1111^(1/2)*t)/1000))/3333).*(t>=0);
fplot(to_plot2,[-10 300]);
axis ([-10 300 -1.2 1.2]);
xlabel ('t'); ylabel ('h2(t)');