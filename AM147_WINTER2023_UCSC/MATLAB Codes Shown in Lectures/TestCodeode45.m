set(groot,'defaultAxesTickLabelInterpreter','latex');  
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

t_initial = 0; t_final = 20;

init_min = -3; init_max = 3; nSample = 10;

%% solve ODE and plot trajectories in the state space
figure(1)

for j=1:10
    
    % randomly generate initial condition within init_min and init_max
    initial_condition(:,j) = init_min + (init_max-init_min)*rand(2,1);
    
    % solve the ODE initial value problem
    options = odeset('RelTol',1e-6,'AbsTol',1e-6);
    [t,y] = ode45(@DynamicsFunc,[t_initial t_final], initial_condition(:,j),options);
    
    plot(y(:,1),y(:,2),'-b','LineWidth',2)
    hold on
    plot(initial_condition(1,j),initial_condition(2,j),'ro','MarkerSize',16,'MarkerFaceColor','red')
    hold on
    grid on
end
set(gca,'FontSize',30)
xlabel('$y_{1}$','FontSize',35)
ylabel('$y_{2}$','FontSize',35,'rotation',0)
hold on
[Y1domain,Y2domain] = meshgrid(-4:0.1:4,-4:0.1:4);
Y1_vector_field = Y2domain;
Y2_vector_field = (1-Y1domain.^2).*Y2domain - Y1domain;
quiver(Y1domain,Y2domain,Y1_vector_field,Y2_vector_field,4,'-r')
hold off
axis tight
%% plot time series
figure(2)
plot(t,y(:,1),'-o',t,y(:,2),'-o','LineWidth',1.5)
set(gca,'FontSize',30)
xlabel('$t$','FontSize',35)
legend('$y_{1}$', '$y_{2}$','FontSize',35,'Location','best','Interpreter','latex')
