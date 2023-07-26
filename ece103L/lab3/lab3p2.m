close all
clear all
clc
clf  % clear figure

%% signal: x, impulse response: h
x = @(time) 5.*(time>=0 & time<10);
h = @(time) (exp(-time./4).*cos((31^(1/2).*time)./4) - (31^(1/2).*exp(-time/4).*sin((31^(1/2).*time)./4))./31).*(0<=time);
x2 = @(time) 2*x(time-10);
xlc = @(time) x(time) + 2*x(time-10);
%% we need two time variables 'tau' and 't'
% 'tau' will be the variable for integration : resolution of 'tau' will 
                        % determine error limit of numerical integration
% 't' will be the variable for introducing time delay h(t-tau) : will
                        % determine the resolution of output signal y(t)
% the result will be in terms of time variable 't'
% y(t)=Integration (x(tau)*h(t-tau))*dtau, with limits of tau=-inf to +inf

dtau = 0.1;   % time step of tau (time), smaller value will improve the 
              % shape of signal 'x' and 'h'

tau = -10:dtau:40;  % 'tau' should cover time scale from -inf to 
                  % +inf, however, we are taking a range that
                  % specifies non-zero region of 'x' and 'h'
                
dT=0.5;   % step for variable 't': will define time resolution of 
          % output signal 'y'
          
% has to be careful while chooseing the limits for 't'
% y(t) will have non-zero value from min(non_zero_x)+min(non_zero_h)+ to
% max(non_zero_x)+ max(non_zero_h)
t = -10:dT:40;  % time variable for the time delay and output signal
y = NaN(1, length (t)); 
y2 = NaN(1, length (t));
ylc = NaN(1, length (t));
y3 = NaN(1, length (t));
test = h(1);
test
 
for ii=1:length(t)  % evaluating integration of x(tau)*h(t-tau)
                    % for a specific time delay t(ii)
    t(ii)

    xh1 = h(t(ii)-tau).*x(tau); 
    xh2 = h(t(ii)-tau).*x2(tau);  
    xhlc = h(t(ii)-tau).*xlc(tau);
    y(ii)=trapz(tau,xh1);

    y2(ii)=trapz(tau,xh2);

    ylc(ii)=trapz(tau,xhlc);

    y3 = y+y2;
                           
    
  
%% plotting in fancy way, good to know what the code does, but not a  
%  necessary requirment
    subplot (5,1,1)
    plot(tau, xlc(tau), 'k-', tau, h(t(ii)-tau), 'b--', t(ii), 0, 'ok');
    xlabel('\tau'); axis ([tau(1) tau(end) -5.0 20.0]); grid;
    legend('x(\tau)','h(t-\tau)');
    axis ([tau(1) tau(end) -11.0 11.0]); grid;

    subplot (5,1,2)
    plot (t, y, 'k', t (ii), y(ii), 'ok');
    xlabel ('t'); ylabel ('y_1(t)');
    axis ([tau(1) tau(end) -7.0 7.0]); grid;
    

    subplot (5,1,3)
    plot (t, y2, 'k', t (ii), y2(ii), 'ok');
    xlabel ('t'); ylabel ('y_2(t)');
    axis ([tau(1) tau(end) -7.0 7.0]); grid;

    subplot (5,1,4)
    plot (t, ylc, 'k', t (ii), ylc(ii), 'ok');
    xlabel ('t'); ylabel ('y_linear comb(t)');
    axis ([tau(1) tau(end) -7.0 7.0]); grid;

    subplot (5,1,5)
    plot (t, y3, 'k', t (ii), y3(ii), 'ok');
    xlabel ('t'); ylabel ('y_3(t)');
    axis ([tau(1) tau(end) -7.0 7.0]); grid;
    drawnow;
    
  end