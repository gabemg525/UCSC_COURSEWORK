%% diff eq of system: D2y+3Dy+2y= Dx, with BC y(0)=0 and vc(0)=5
% impulse response: x=detla(t), B.C. hz(0)=0, Dhz(0)=1
h_0=dsolve('2*D2hz+Dhz+4*hz=0','hz(0)=0','Dhz(0)=1','t');
h=diff(h_0);
disp(['impulse response h(t) = (',char(h),')u(t)']);
to_plot=@(t) (exp(-t/4)*cos((31^(1/2)*t)/4) - (31^(1/2)*exp(-t/4)*sin((31^(1/2)*t)/4))/31).*(t>=0);
fplot(to_plot,[-10 30]);
xlabel ('t'); ylabel ('h(t)');
