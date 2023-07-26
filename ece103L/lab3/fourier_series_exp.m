

function [Ck]=fourier_series_exp(x,t,Nk,p)

% Ck = exponential fourier series cofficient  
% x = single period of a signal
% t = time corrosponding to 'x'
% Nk = (optional input) number of exponential terms
% p = plotting option ; p=0, no plots, p = 1 plot Ck vs k and reconstructed signal  
% dT = t(2)-t(1) = temporal resolution of signal (x)
% T = peiod of signal 'x'
% w0= angular frequency of signal 'x' 

    
    dT=t(2)-t(1);
    T= dT*length(t);
    w0=2*pi/T;   

    % Check the number of inputs, 'nargin' returns number of input arguments 
    if nargin <2
        error('Not enough input argument!')
    elseif nargin == 2
        Nk=101;   % you can set any default value you like 
        p=0;      % not plots
    elseif nargin ==3
        p=0;      % not plots
    end
    k=-floor(Nk/2):floor(Nk/2); % if Nk=11, k=-5:5; if Nk=12, k=-6:6


    %% evaluate Ck
    for ii=1:length(k)
        Ck(ii)= (1/T)*trapz(t, x.*exp(-j*k(ii)*w0*t));
        a=abs(Ck).*exp(angle(-j.*Ck))
    end
%% plot spectrum and reconstructed signal     
    if p==1

        winit=w0*k; 
        figure (1) 
        subplot(2,1,1) 
        stem(winit,abs(Ck))
        title('absolute val of CK vs omegak')
        subplot(2,1,2)
        title('Ck Angle vs omegak angle') 
        stem(winit,angle(Ck)*180/pi); 

        % plot 3 cycles of the signal 'x' and the reconstructed signal
 
        xrep=repmat(x,1,3);
  
        text=linspace(t(1),t(1)+(length(xrep)-1)*(t(2)-t(1)),length(xrep));

        xr2 = zeros(1,length(text));
        for ii=1:length(k)
            xr2=xr2+Ck(ii)*exp(j*k(ii)*w0*text);
        end
        figure(2)

        subplot(2,1,1), plot(text,xrep)
        xlabel('Time'), ylabel('x')
        title('initial')
        subplot(2,1,2), plot(text,xr2)
        xlabel('Time'), ylabel('x')
        title('reconstructed')
        %
    end
     
end