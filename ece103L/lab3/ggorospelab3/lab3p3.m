
x = @(t) (cos(100*pi*t) + sin(400*pi*t) - cos(800*pi*t)).*(t>=0);
h = @(t) (400*exp(-200*t)*cos(500*pi*t)).*(t>=0);

dT=0.0001;
t = -0.1:dT:0.1;
wt = NaN(1, length (t)); 
xt = NaN(1, length (t)); 
ht = NaN(1, length (t)); 
for i=1:length(t)
    t_i = t(i);
    wt(i) = sin(400*pi*t_i);
    xt(i) = x(t_i);
    ht(i) = h(t_i);
end
yt = conv(xt,ht)*dT; 

%%%%%%

subplot (3,1,1)
plot(t,wt);
xlabel ('t'); ylabel ('w(t)');

subplot (3,1,2)
plot(t,xt);
xlabel ('t'); ylabel ('x(t)');

ty = -0.2:dT:0.2;
subplot (3,1,3)
plot(ty,yt);
xlabel ('t'); ylabel ('y(t)');
axis ([-0.1 0.1 -1 1]);