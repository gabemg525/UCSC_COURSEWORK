x = @(t) (-2*t + 10) .* (t >= -5 & t < 5) + 10 .* (t >= 5 & t <= 10);

t = -10:0.01:15;

figure;
plot(t, x(t));
title('Plot of x(t)');
xlabel('t');
ylabel('x(t)');

figure;

subplot(2,2,1);
plot(t, x(t+2));
title('x(t+2)');
xlabel('t');
ylabel('x(t)');

subplot(2,2,2);
plot(t, x(t-3));
title('x(t-3)');
xlabel('t');
ylabel('x(t)');

subplot(2,2,3);
plot(t, x(-t));
title('x(-t)');
xlabel('t');
ylabel('x(t)');

subplot(2,2,4);
plot(t, -3*x(-t+4));
title('-3x(-t+4)');
xlabel('t');
ylabel('x(t)');