close all; clear; clc;

% search interval from the geometry
a = 1; b = 2;
% use bisection method to compute the root
tol = 1e-4; maxiter = 1000;
% call bisection
r_approx = bisection(a, b, @func, tol, maxiter)
