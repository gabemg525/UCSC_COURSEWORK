% Define the transfer function
num = [10];
den = [1 5 10];
G = tf(num, den);

% Create the Bode plot
bode(G);
grid on;

% Add title and labels
title('Bode Plot');
xlabel('Frequency (rad/s)');
ylabel('Magnitude (dB), Phase (degrees)');
