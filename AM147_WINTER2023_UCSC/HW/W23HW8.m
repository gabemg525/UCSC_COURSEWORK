close all; clear; clc;

set(groot,'defaultAxesTickLabelInterpreter','latex');  
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

% data
t = (1:500)';
x = 2*sin(0.1*t) + 3*cos(0.01*t) + 4*sin(0.02*t);

noise = -ones(size(x)) + 2*rand(size(x));

x_noisy = x + noise;

figure(1)
plot(t,x,'-k','LineWidth',2)
hold on
plot(t,x_noisy,'-b','LineWidth',1)
hold on
set(gca,'FontSize',30)
xlabel('$t$','FontSize',35); ylabel('$x$','FontSize',35,'rotation',0)
axis tight

%% recover an estimate xhat for the original unknown signal x from x_noisy





beta = [1; 10; 100];

% line_style = {'-','-','-'}; line_color = {'r','c','g'};
% 
% for j=1:length(beta)
%     
%     % least squares estimate via A\b
%     xhat(:,j) = ; 
%     
%     plot(t,xhat(:,j),'color',line_color{j},'linestyle',line_style{j},'LineWidth',2)
%     hold on
% end
% legend('$x_{\rm{true}}$','$x_{\rm{noisy}}$','$\beta = 1$','$\beta = 10$','$\beta = 100$')
% hold off
