Nk = 51;

p = 1;
%setting resolution of 0.001
t = [-5:.001:5];

x = @(t) 0.6.*(heaviside(t+2)-(cos(pi*t)+1).*[heaviside(t+1)-heaviside(t-1)]-heaviside(t-2));

x_t = x(t);

fourier_series_exp(x_t,t,Nk,p);

