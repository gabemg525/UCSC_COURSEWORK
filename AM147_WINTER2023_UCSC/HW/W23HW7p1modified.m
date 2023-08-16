close all; clear; clc;

set(groot,'defaultAxesTickLabelInterpreter','latex');  
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

% year
yr = [1971; 1972; 1974; 1978; 1982; 1985; 1989;
    1993; 1997; 1999; 2000; 2002; 2003];
% number of transistors
num_transistor = [2250; 2500; 5000; 29000;
    120e3; 275e3; 1180e3; 3100e3; 7500e3;
    24e6; 42e6; 220e6; 410e6];
% plot of data
figure(1)
semilogy(yr,num_transistor,'bo','MarkerSize',10,'LineWidth',2)
set(gca,'FontSize',30)
xlabel('Year','FontSize',35); ylabel('Number of transistors','FontSize',35)
axis tight
hold on

y = ;
A = ;
% least square estimate
theta = A\y;
% plot the estimate
plot(yr,10.^(theta(1) + theta(2)*(yr-1970)),'-r','LineWidth',2)

% predict number of transistors in 2020
pred_2020 = ;