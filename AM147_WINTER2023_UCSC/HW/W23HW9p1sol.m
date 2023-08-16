close all; clear; clc;

set(groot,'defaultAxesTickLabelInterpreter','latex');  
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

t_initial = 0; t_final = 100;

init_cond = [995; 5; 0; 0];

N = sum(init_cond); % total constant population

%% ode45
% compute the solutions using ode45
[t,y] = ode45(@(t,y) SIRD_dynamics(t,y,N), [t_initial t_final], init_cond);

% make ode45 plots
figure(1)
plot(t,y(:,1),'-b',t,y(:,2),'-r',t,y(:,3),'-g',t,y(:,4),'-k','LineWidth',2)
set(gca,'FontSize',30)
xlabel('$t$','FontSize',35)
hold on

%% RK4
dt = 0.5; % fixed step size

t_RK4 = t_initial:dt:t_final; % uniformly discretized time vector

% preallocate for RK4 solution
y_RK4 = [init_cond, zeros(numel(init_cond),numel(t_RK4)-1)];

% compute the solutions using RK4
for k = 1:numel(t_RK4)-1 
    
    y_RK4(:,k+1) = FixedStepRK4(@SIRD_dynamics, t_RK4(k), y_RK4(:,k), dt, N);
    
end

% make RK4 plots
plot(t_RK4,y_RK4(1,:),'bo',t_RK4,y_RK4(2,:),'ro',t_RK4,y_RK4(3,:),'go',t_RK4,y_RK4(4,:),'ko')
legend('$S(t)$ from ode45','$I(t)$ from ode45','$R(t)$ from ode45','$D(t)$ from ode45',...
'$S(t)$ from RK4','$I(t)$ from RK4','$R(t)$ from RK4','$D(t)$ from RK4', ...
'FontSize',35,'Location','best','Interpreter','latex')
legend boxoff