function dydt = DynamicsFunc(t,y)

dydt(1,:) = y(2);

dydt(2,:) = (1-y(1)^2)*y(2) - y(1);

% returning dydt as column vector