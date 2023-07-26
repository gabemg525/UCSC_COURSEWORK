t_values = linspace(0, 1, 15);
x_values = zeros(length(t_values),1);
max_x = 0;
min_x = 0;
i_over_4 = zeros(0);
for i = 1:length(t_values)
    x_values(i) = 4*cos(2*pi*t_values(i)+0.2) + 3*sin((pi^2)*t_values(i));
    if i==1
        max_x = x_values(i);
        min_x = x_values(i);
    end
    if x_values(i) > 4
        i_over_4 = [i_over_4 i];
    end
    if max_x < x_values(i)
        max_x = x_values(i);
    end
    if min_x > x_values(i)
        min_x = x_values(i);
    end
    

end
disp(x_values);
disp(i_over_4);
disp(max_x);
disp(min_x);
