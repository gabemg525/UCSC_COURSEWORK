function slope = SIRD_dynamics(t, y)
    
    S = y(1);
    I = y(2);

    slope = [
        (-0.45/1000)*I*S; 
        (0.45/1000)*I*S - 0.04*I - 0.01*I; 
        (0.04*I);
        (0.01*I);
        ];
end