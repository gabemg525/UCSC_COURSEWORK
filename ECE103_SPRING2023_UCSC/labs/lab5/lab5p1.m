G = @(w) (2).*(abs(w)>=5 & abs(w)<=10);
Y = @(w) G(w-5);
w=-31.4:0.01:31.4;
t=-100:0.1:100;
for ii=1:length(t)
    g(ii)=trapz(w,(1/(2*pi))*G(w).*exp(j*w*t(ii)));
    y(ii)=trapz(w,(1/(2*pi))*Y(w).*exp(j*w*t(ii)));

end




subplot (3,1,1)
%plot(w,G(w));
plot(w,abs(Y(w)));
xlabel ('w'); ylabel ('Y(w)');

subplot (3,1,2)
%plot(t,real(g));
plot(t,real(y));
xlabel ('t'); ylabel ('Re(y(t))');

subplot (3,1,3)
%plot(t,imag(g));
plot(t,imag(y));
xlabel ('t'); ylabel ('Im(y(t))');
