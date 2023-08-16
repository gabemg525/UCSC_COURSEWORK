close all; clear; clc;
set(groot,'defaultAxesTickLabelInterpreter','latex');  
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');
% generate datapoints
x_data = (-1:0.1:1)';
y_data = 1./(1 + 25*x_data.^2);
% plot datapoints
figure(1)
plot(x_data,y_data,'ko','LineWidth',2,'MarkerFaceColor','k')
xlabel('$x$','FontSize',30); ylabel('$y$','FontSize',30,'rotation',0); 
set(gca,'FontSize',30)
hold on
% blocks of the coefficient matrix
for i=1:numel(x_data)-1
    X{i} = [x_data(i) 1 ; x_data(i+1) 1];
end
% set up and solve the linear system
A = blkdiag(X{:});
y = repelem(y_data, [1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 1]);
c = A\y;
% plot the computed spline interpolant
for i=1:numel(x_data)-1
    line_idx = 2*i-1;
    % straight line segment as function handle
    f = @(x) c(line_idx)*x + c(line_idx+1);
    % plot the line segment
    fplot(f, [x_data(i), x_data(i+1)], '-r', 'Linewidth',2)
    hold on
end