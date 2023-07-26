G = @(w) (2).*(abs(w)>=5 & abs(w)<=10);
H = @(freq) (5*abs(freq)).*(abs(freq)<=20);
M = @(freq) G(freq).*H(freq);
w=-31.4:0.01:31.4;
t=-100:0.1:100;
for ii=1:length(t)

    m(ii)=trapz(w,(1/(2*pi))*M(w).*exp(j*w*t(ii)));

end


N = numel(t);
m = rand(1,N);
energy = sum(m .* m);
m_f = fft(m,numel(w));
energy_p = sum(abs(m_f) .^ 2) / numel(w);



energy
energy_p