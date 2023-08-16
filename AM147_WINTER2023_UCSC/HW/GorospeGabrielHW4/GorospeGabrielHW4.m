fn = @(x) m + epsilon*sin(x);
m = 0.5;
epsilon = 0.5;

k = 0;
x_k = 0;

random_init_guesses = rand(1,50);
XK = zeros(50, 20);
for i = 1:50
    x_k = random_init_guesses(i);
    for k = 1:20
        x_k = fn(x_k);
        XK(i,k) = x_k;
        
    end
end
figure;
plot(1:20, XK, '.');
xlabel('k');
ylabel('x_k');