x_values = linspace(-2*pi, 2*pi);
sinc1 = MySinc(x_values);
sinc2 = sinc(x_values);
plot(x_values, sinc1,x_values,sinc2);
legend('MySinc', 'matlab sinc');
function y = MySinc(x)
    
    for i = 1:length(x)
        if x(i) == 0
            y(i) = 1;
        else
            y(i) = sin(x(i))/x(i);
        end

    end
end