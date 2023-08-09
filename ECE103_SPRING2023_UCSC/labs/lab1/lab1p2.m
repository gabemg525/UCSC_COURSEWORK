t_vals = [0, 0.1, 0.2, 0.3, 0.4];
f_vals = [10, 15, 20];

x = zeros(length(t_vals), length(f_vals));


for i = 1:length(f_vals)
    for j = 1:length(t_vals)
        x(j, i) = 3*cos(2*pi*f_vals(i)*t_vals(j) + 0.1);
    end
end
