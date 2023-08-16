close all; clear; clc;

set(groot,'defaultAxesTickLabelInterpreter','latex');
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

% create vectors
x = -pi:0.1:pi;

y1 = sin(x); y2 = cos(x);

t = 0:0.1:20;
xx = cos(t); yy = sin(t); zz = t;

figure(1)
plot(x,y1,'-ro','LineWidth',2)
hold on
plot(x,y2,'-bo','LineWidth',2)
xlabel('$x$','FontSize',30,'Interpreter','latex'); 
ylabel('$y_1,y_2$','FontSize',30,'Interpreter','latex','rotation',0);
set(gca,'FontSize',30)
axis tight

figure(2)
plot3(xx,yy,zz,'-k','LineWidth',2)
hold on
plot3(xx(50),yy(50),zz(50),'go','MarkerFaceColor','g')
axis tight
grid on
xlabel('$\cos(t)$','FontSize',30,'Interpreter','latex'); ylabel('$\sin(t)$','FontSize',30,'Interpreter','latex'); zlabel('$t$','FontSize',30,'Interpreter','latex','rotation',0);
set(gca,'FontSize',30)

figure(3)
[X,Y] = meshgrid(-5:0.1:5,-5:0.1:5);
Z = Y.*sin(X) - X.*cos(Y);
surf(X,Y,Z)
xlabel('$x$','FontSize',30,'Interpreter','latex')
ylabel('$y$','FontSize',30,'Interpreter','latex')
zlabel('$z$','FontSize',30,'Interpreter','latex')
set(gca,'FontSize',30)
