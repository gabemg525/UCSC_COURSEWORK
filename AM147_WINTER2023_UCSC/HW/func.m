function func_val = func(x)

func_val = x.^2 .* acos(x/2) + acos(1 - ((x.^2)./2)) - 0.5*x.*sqrt(4-x.^2) - (pi/2);