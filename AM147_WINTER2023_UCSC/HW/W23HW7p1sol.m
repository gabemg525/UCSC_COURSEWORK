close all; clear; clc;

% I use cell to store the solutions but the student's don't have to
xhat = cell(1,4); % preallocate

for k=5:8
    
    A = [1 1; 10^(-k) 0; 0 10^(-k)];
    
    b = [-10^(-k); 1 + 10^(-k); 1 - 10^(-k)];
    
    % hardcoded analytical solution (independent of k)
    xhat{k-4}.analytical = [1; -1];
    
    % solve by QR decomposition via backslash
    xhat{k-4}.QR = A\b;
    
    % numerically solve normal equation as square linear system
    xhat{k-4}.normal = (A'*A)\(A'*b);
    
end
    