g = @(t) 3*pi*sin(8*pi*t + 1.3).*cos(4*pi*t - 0.8).*exp(sin(12*pi*t));
t = 0.25:0.001:0.75;
y = g(t);
E = trapz(t, abs(y).^2);
P = E / (0.5 * (0.75 - 0.25));
fprintf('Energy: %f\n', E)
fprintf('Power: %f\n', P)