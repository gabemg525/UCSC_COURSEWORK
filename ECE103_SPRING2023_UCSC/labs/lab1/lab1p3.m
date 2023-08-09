omega_values = [35, 40, 45];

max_t = zeros(length(omega_values),1);
for i = 1:length(omega_values)
    t = 0;
    p = 0;
    while t<10
        y1 = exp(1.2)*cos(omega_values(i)*t);
        y2 = t^3;
        if  y1< 10 && y2< 10 && t>=max_t(i)
            max_t(i) = t;
        end
        t = t + 0.01;
    end
end
disp(max_t)
%max_t has the same answer for different values of omega as amplitude of
%the function it is applied to will not exceed e^1.2, which is smaller than