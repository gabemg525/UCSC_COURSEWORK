close all; clear; clc;

syms t;
f = @(t) 4*t.^4 -6*t.^2 - 11/4;
f_prime = eval(['@(t)' char(diff(f(t)))]);

figure(1)
fplot(f,[-2, 2],'--k','Linewidth', 2)
grid on
xlabel('$x$','FontSize',30,'Interpreter','latex'); 
ylabel('$f(x)$','FontSize',30,'Interpreter','latex','rotation',0);
hold on
a = 0.5; plot(a, f(a), 'ro', 'LineWidth', 2, 'MarkerSize', 10)
hold on
yline(0,'-k','LineWidth',2);
hold on
tangent_a = @(t) f_prime(a)*(t - a) + f(a);
fplot(tangent_a,[-2, 2],'-r','Linewidth', 1)
hold on
b = -0.5; plot(b, f(b), 'ro', 'LineWidth', 2, 'MarkerSize', 10)
hold on
tangent_b = @(t) f_prime(b)*(t - b) + f(b);
fplot(tangent_b,[-2, 2],'-r','Linewidth', 1)
set(gca,'FontSize',24);



numIter = 10; % number of iterations
%x0 = 0.4; % initial guess
x0 = -2:0.1:2;
x = [x0; zeros(numIter,numel(x0))]; % initialize

for k=1:numIter
    for j=1:numel(x0)
    x(k+1,j) = (12*(x(k,j)).^4 - 6*(x(k,j)).^2 + 11/4)/(16*(x(k,j)).^3 -12*x(k,j));
    end
end
%x

figure(2)
for j=1:numel(x0)
    plot(1:numIter+1,x(:,j),'-bo','LineWidth',1)
    hold on
end
xlabel('Iteration index $k$','FontSize',30,'Interpreter','latex'); 
ylabel('Newton iterates $x_{k}$','FontSize',30,'Interpreter','latex');
set(gca,'FontSize',30)
axis tight