F = @(freq) (2+freq).*(abs(freq)>=3 & abs(freq)<=10);
H = @(freq) (3*(abs(freq).^2)-9).*(abs(freq)>=4 & abs(freq)<=20);
Z = @(freq) F(freq).*H(freq);
w=-20:0.001:20;
t=-50:0.1:50;
for ii=1:length(t)
    q(ii)=trapz(w,(1/(2*pi))*F(w).*exp(j*w*t(ii)));
    p(ii)=trapz(w,(1/(2*pi))*Z(w).*exp(j*w*t(ii)));

end




subplot (6,1,1)
plot(w,F(w));
xlabel ('t'); ylabel ('w(t)');

subplot (6,1,2)
plot(t,q);


subplot (6,1,3)
plot(t,imag(q));

subplot (6,1,4)
plot(w,abs(Z(w)));

subplot (6,1,5)
plot(t,real(p));

subplot (6,1,6)
plot(t,imag(p));