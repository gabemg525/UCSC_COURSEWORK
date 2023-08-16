function rk4 = FixedStepRK4(y, t_range, init_conditions)

    rk4 = [995, 5, 0, 0]; %initialize output matrix
    dt = 0.5; %step size
    yk_old = init_conditions; %initialize yk for recursive

    for t = 0:dt:t_range %from 0 to 100 with step size 0.5

        k1 = dt * SIRD_dynamics(t, yk_old)'; %should be vec of all vars
        k2 = dt * SIRD_dynamics(t + dt/2, yk_old + k1/2)';
        k3 = dt * SIRD_dynamics(t + dt/2, yk_old + k2/2)';
        k4 = dt * SIRD_dynamics(t + dt, yk_old + k3)';
        yk = yk_old + (1/6) * (k1 + 2*k2 + 2*k3 + k4); %4x1 vec?
        yk_old = yk; %set old to new
        rk4 = [rk4; yk]; %append matrix
    end
    rk4(end,:) = [];
end