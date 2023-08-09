t_values = 0:0.1:10;
t_length = length(t_values);
s1_values = zeros(t_length,1);
s2_values = zeros(t_length,1);
s3_values = zeros(t_length,1);
for i = 1:t_length
    s1_values(i) = sin(2*pi*0.2*t_values(i));
    s2_values(i) = sin(2*pi*0.425*t_values(i)+0.4);
    s3_values(i) = s1_values(i) + s2_values(i);
end
plot(t_values, s1_values, t_values, s2_values, t_values, s3_values);
legend('s1', 's2', 's3');

% Add axis labels and a title
xlabel('t Values');
ylabel('s Values');