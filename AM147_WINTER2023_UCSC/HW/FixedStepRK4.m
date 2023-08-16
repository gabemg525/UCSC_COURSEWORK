function y_next = FixedStepRK4(f,t_now,y_now,dt,param)

k1 = dt*f(t_now,y_now,param);

k2 = dt*f(t_now + 0.5*dt, y_now + 0.5*k1, param);

k3 = dt*f(t_now + 0.5*dt, y_now + 0.5*k2, param);

k4 = dt*f(t_now + dt, y_now + k3, param);

y_next = y_now + (1/6)*(k1 + 2*k2 + 2*k3 + k4);