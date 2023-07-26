syms s t
R = 1;
f = (s^3+3*s^2+16*s+32) / (2*s*(s+3)*(s+j*4)*(s-j*4));
L = ilaplace(f,t);
disp(['ilaplace(f) = ',char(L)]);