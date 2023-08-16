close all; clear; clc;

set(groot,'defaultAxesTickLabelInterpreter','latex');  
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

A = [1 1 1 -2 -2;
    1 2 4 -10 -20;
    1 3 9 -27 -81;
    1 4 16 4 16;
    1 5 25 20 100];

b = [2; 5; 9; -1; -4];

x = A\b;

t = -6:0.01:6;

f = (x(1) + x(2)*t + x(3)*t.^2)./(1 + x(4)*t + x(5)*t.^2);

figure(1)
% plot the interpolated curve
plot(t,f,'-k','LineWidth',2)
set(gca,'FontSize',30)
xlabel('$t$','FontSize',30); 
ylabel('$f(t)$','FontSize',30,'rotation',0);
grid on
hold on
% plot given points (students don't need to do this)
t_data = [1 2 3 4 5];
plot(t_data,b,'ro','MarkerSize',10,'LineWidth',2) 

