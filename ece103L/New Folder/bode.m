% Constants
R = 10; % Resistance (Ω)
L = 1e-3; % Inductance (H)
C = 10e-6; % Capacitance (F)

% Frequency range
f = logspace(1, 5, 1000); % Frequencies from 10 to 100,000 Hz (logarithmic scale)
w = 2 * pi * f; % Angular frequencies (rad/s)

% Transfer function H(ω)
H = -w.^2 * L * C ./ (1 + 1j * w * L / R - w.^2 * C * L);

% Magnitude response in decibels
magnitude_dB = 20 * log10(abs(H));

% Phase response
phase = angle(H);

% Plot magnitude response in decibels
subplot(2, 1, 1);
semilogx(f, magnitude_dB);
xlabel('Frequency (Hz)');
ylabel('|H(\omega)| (dB)');
title('Magnitude Response');

% Plot phase response
subplot(2, 1, 2);
semilogx(f, rad2deg(phase));
xlabel('Frequency (Hz)');
ylabel('Phase (degrees)');
title('Phase Response');
