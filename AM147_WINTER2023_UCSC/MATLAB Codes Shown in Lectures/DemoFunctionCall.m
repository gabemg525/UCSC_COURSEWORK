close all; clear; clc;

set(groot,'defaultAxesTickLabelInterpreter','latex');
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

% create input data 
x_test = rand(100,1);

% create parameter vector
abc_vec = [5; -2; 3];  

% call function
y = MyFunc(abc_vec, x_test);

% make a plot
figure(1)
plot(x_test, y, 'bo','MarkerSize', 10,'LineWidth',1.2)
xlabel('$x$','FontSize',30,'Interpreter','latex'); 
ylabel('$y$','FontSize',30,'Interpreter','latex','rotation',0);
set(gca,'FontSize',30)
