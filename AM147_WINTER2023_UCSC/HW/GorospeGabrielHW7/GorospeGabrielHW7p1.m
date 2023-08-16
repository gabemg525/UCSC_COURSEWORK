for k = 5:8

    A = [1 1; 10^(-k) 0; 0 10^(-k)];
    b = [-10^(-k); 1+10^(-k); 1-10^(-k)];
    xhat_analytical = [1; -1];   
    [Q,R] = qr(A);
    xhat_QR = R \ (Q' * b);
    xhat_normal = A \ b;

    fprintf('k = %d\n', k);
    fprintf('xhat_analytical = [%.10f; %.10f]\n', xhat_analytical);
    fprintf('xhat_QR = [%.10f; %.10f]\n', xhat_QR);
    fprintf('xhat_normal = [%.10f; %.10f]\n', xhat_normal);
    fprintf('\n');
end