close all; clear; clc;

set(groot,'defaultAxesTickLabelInterpreter','latex');
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

% parameters
m = 0.5; eps = 0.5;

g = @(t) m + eps*sin(t);

numIter = 20; nSample = 50; 

x0 = rand(nSample,1);

x = [x0'; zeros(numIter,nSample)];

% recursion
for j=1:nSample
    for k=1:numIter
        x(k+1,j) = g(x(k,j));       
    end    
end

figure(1)
plot(x,'-bo')
axis tight
xlabel('Iteration index $k$','FontSize',30,'Interpreter','latex')
ylabel('Iterate $x_{k}$','FontSize',30,'Interpreter','latex')
set(gca,'FontSize',30)
