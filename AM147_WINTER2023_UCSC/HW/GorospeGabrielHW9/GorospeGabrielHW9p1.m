tspan = 0:1:100;

y0 = [995, 5, 0, 0];

[t,y] = ode45(@(t,y) SIRD_dynamics(t, y), tspan, y0);

hold on;
plot(t, y(:,1,:), 'b');
plot(t, y(:,2,:), 'r');
plot(t, y(:,3,:), 'g');
plot(t, y(:,4,:), 'k');
legend('S','I','R','D')
y2 = FixedStepRK4(SIRD_dynamics(t,y), 100, y0);
t2 = 0:0.5:100;
size(y2)
size(t2)

plot(t2, y2(:,1,:), 'bo');
plot(t2, y2(:,2,:), 'ro');
plot(t2, y2(:,3,:), 'go');
plot(t2, y2(:,4,:), 'ko');
legend('S','I','R','D')
hold off;