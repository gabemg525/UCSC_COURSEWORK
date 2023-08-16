function dydt = SIRD_dynamics(t,y,N)

% parameters
beta = 0.45; gamma = 0.04; mu = 0.01;

dydt(1) = -(beta/N)*y(2)*y(1);

dydt(2) = (beta/N)*y(2)*y(1) - gamma*y(2) - mu*y(2);

dydt(3) = gamma*y(2);

dydt(4) = mu*y(2);

dydt = dydt';