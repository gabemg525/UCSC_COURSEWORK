close all; clear; clc;

set(groot,'defaultAxesTickLabelInterpreter','latex');  
set(groot,'defaulttextinterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

% Time interval
t = (1900:10:2000)';

% US population (in millions)
p = [75.995 91.972 105.711 123.203 131.669 ...
     150.697 179.323 203.212 226.505 249.633 281.422]';

% Plot
plot(t,p,'ko','LineWidth',2,'MarkerFaceColor','k');
axis([1900 2020 0 400]);
title('United States Population: Census Data 1900-2000','fontsize',20);
xlabel('Years','fontsize',30); 
ylabel('Millions','fontsize',30); 
set(gca,'FontSize',30)

%% Construct 11-by-11 Vandermonde matrix
n = length(t);
s = (t-1950)/50; % scaled time
X = zeros(n); X(:,end) = 1;
for j = n-1:-1:1 
    X(:,j) = s .* X(:,j+1); 
end

%% Least square
v = (1900:2020)';
x = (v-1950)/50;

cla
plot(t,p,'ko','LineWidth',2,'MarkerFaceColor','k','MarkerSize',10); 
hold on; 
axis([1900 2020 0 400]); colors = hsv(11); labels = {'data'};
for d = 1:4
    c = X(:,n-d:n)\p; % coefficient vector from least square
    y = polyval(c,x);
    z = polyval(c,11);
    plot(v,y,'color',colors(d,:),'LineWidth',2);
    labels{end+1} = ['degree = ' int2str(d)];
    hold on;
end
legend(labels,'Location','best')
% 2010 actual census data
plot(2010,310,'ks','MarkerSize',16,'LineWidth',2,'DisplayName','2010 data')

title('United States Population: Census Data 1900-2000','fontsize',20);
xlabel('Years','fontsize',30); 
ylabel('Millions','fontsize',30); 
set(gca,'FontSize',30)

hold off
