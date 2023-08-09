
f0 = 160;
N_1 = 51; 
N_2 = 101; 
df1 = 0.04; 
df2 = 0.02; 
t = 0:0.001:200;

y1 = zeros(size(t));
y2 = zeros(size(t));
for n = 1:N_1
    fi = f0 + (n-1)*df1;
    y1 = y1 + 10*cos(2*pi*fi*t);
end


for n = 1:N_2
    fi = f0 + (n-1)*df2;
    y2 = y2 + 10*cos(2*pi*fi*t);
end

figure
plot(t, y1, 'b', t, y2, 'r')
xlabel('Time (s)')
ylabel('Amplitude')
legend('N = 51, \Delta f = 0.04 Hz', 'N = 101, \Delta f = 0.02 Hz')