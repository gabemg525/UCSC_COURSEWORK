syms s t
R = 1;
f = 1 / (s^6+3.87*s^5+7.46*s^4+9.14*s^3+7.46*s^2+3.87*s+1);
L = ilaplace(f,t);
disp(['ilaplace(f) = ',char(L)]);