% Define the angular frequency
w_0 = 2 * pi * 10;  % Example value: 10 rad/s

% Define the time vector
t = linspace(0, 1, 1000);  % Time range: 0 to 1 second

% Compute the signal
x_t = cos(w_0 * t);

% Compute the Fourier transform
X_w = fft(x_t);


% Compute the frequency axis
N = length(X_w);
f = (0:N-1) / (t(end) - t(1));

% Plot the magnitude spectrum
figure;
stem(f, abs(X_w));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Fourier Transform of cos(w_0 * t)');
grid on;
