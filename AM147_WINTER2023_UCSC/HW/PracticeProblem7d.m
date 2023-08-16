close all; clear; clc;

L = 1; % Length of the rod
T = 1; % Total time
alpha = 1; % Thermal diffusivity

M = 100; % Number of partitions or intervals along the rod 
N = 1000; % time partitions

dx = L/M; dt = T/N;

lambda = alpha*dt/(dx*dx);

a = 1- 2*lambda; b = lambda;

for i=1:M+1
    x(i) = (i-1)*dx; % grid points along the rod
    u0(i) = sin(pi*x(i)/L); % Initial heat distribution
    u(i) = u0(i);
end

set(0,'defaulttextinterpreter','latex')

for k=1:5 % time steps
    u_old = u;
    for i=2:M % location index along the rod
        u(i) = a*u_old(i) + b*(u_old(i+1) + u_old(i-1)); % Temperature at location index i
    end
    u_exact = u*exp(-(alpha*k*dt)/(L^2)); % Analytical solution
    plot(x,u,'-b','LineWidth',2) % Plot FTCS approximate solution
    hold on
    plot(x,u_exact,'--r','LineWidth',2) % Plot analytical solution
    hold on
end
plot_init = plot(x,u0,'-g','LineWidth',2); % Plot initial heat distribution
xlabel('$x$','fontsize',30); ylabel('$u(x,t)$','fontsize',30,'Rotation',0);
set(gca,'FontSize',18)
legend(plot_init,{'Initial condition $u(x,0)=\sin(\pi x/L)$'})
