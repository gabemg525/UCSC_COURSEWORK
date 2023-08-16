close all; clear; clc;
set(groot,'defaultAxesTickLabelInterpreter','latex');  
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

format long;

t = -3:0.1:3; 
f = t.^3 + t - 1;

figure(1)
plot(t,f,'--k','Linewidth', 2)
grid on
hold on
yline(0,'-k','LineWidth',2);
hold on

numIter = 10; x0 = 3;
x = [x0; zeros(numIter,1)]; % initialize
initial_pt = scatter(x0,0,80,'MarkerFaceColor','r','MarkerEdgeColor','k');
initial_pt.MarkerFaceAlpha = 0.2;
hold on
for k=1:numIter
    x(k+1) = (2*(x(k))^3 + 1)/(3*(x(k))^2 + 1);
    newton_pts = scatter(x(k+1),0,80,'MarkerFaceColor','r','MarkerEdgeColor','k');
    newton_pts.MarkerFaceAlpha = 0.2;
    hold on
end
set(gca,'FontSize',30)
xlabel('$x$','FontSize',30); ylabel('$f(x)$','FontSize',30,'rotation',0);
x