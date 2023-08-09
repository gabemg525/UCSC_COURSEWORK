G = @(w) (2).*(abs(w)>=5 & abs(w)<=10);
H = @(freq) (5*abs(freq)).*(abs(freq)<=20);
M = @(freq) G(freq).*H(freq);
w=-31.4:0.01:31.4;
t=-100:0.1:100;
for ii=1:length(t)

    m(ii)=trapz(w,(1/(2*pi))*M(w).*exp(j*w*t(ii)));

end




subplot (2,1,1)
%plot(w,abs(M(w)));
%xlabel ('w'); ylabel ('magnitude M(w)');
plot(t,real(m));
xlabel ('t'); ylabel ('Re(m(t))');


subplot (2,1,2)
%plot(w,angle(M(w)));
%xlabel ('w'); ylabel ('phase of M(w)');
plot(t,imag(m));
xlabel ('t'); ylabel ('Im(m(t))');


%w1 = -5*pi:.01:5*pi;
%XX = subs(X,w,w1);
%plot(w1,angle(XX));
%xlim([-5*pi 5*pi])
%title(' Phase of DTFT in 5 periods')