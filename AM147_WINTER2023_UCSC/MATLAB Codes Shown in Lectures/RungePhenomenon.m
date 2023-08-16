close all; clear; clc;

set(groot,'defaultAxesTickLabelInterpreter','latex');  
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

% generate data
n = 5;
x = rand(n,1);
ymin = -3; ymax = 3;
y = ymin + (ymax - ymin)*rand(n,1);
% plot the data
figure(1)
plot(x,y,'bo','MarkerFaceColor','b','MarkerSize',10)
hold on
grid on
% construct the Vandermonde matrix
A = fliplr(vander(x));
% solve linear system
c = A\y;
% evaluate the interpolating polynomial on a grid
x1 = 0:0.01:1;
y1 = polyval(flipud(c),x1);
% plot the interpolating polynomial
plot(x1,y1,'-r','LineWidth',2)
set(gca,'FontSize',30)
xlabel('$x$','FontSize',30); 
ylabel('$y$','FontSize',30,'rotation',0);
