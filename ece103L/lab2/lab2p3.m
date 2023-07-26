t = -20:0.1:20;
x = t.*exp(-0.15*t);

xlabel('t');
ylabel('x(t)');


xe = zeros(size(t));

xlabel('t');
ylabel('x_e(t)');


t1 = -20:0.1:0;
xo1 = -t1.*exp(0.15*t1);
t2 = 0.1:0.1:20;
xo2 = t2.*exp(-0.15*t2);

xo = [xo1, xo2];

y = xe + xo;
plot(t, x, t, xe, t, xo, t, y);
xlabel('t');
ylabel('x(t)');
legend('a','b','c','d');
title('Odd Decomposition of x(t)');