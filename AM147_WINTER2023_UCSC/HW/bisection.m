function approx_root = bisection(a, b, func, epsilon, max_iter)

lo = a; hi = b;

iter = 1; % initialize

while (abs((hi - lo)/2.0) > epsilon) && (iter <= max_iter)
    
    mid = (hi + lo)/2.0;
    
    if func(mid) == 0
        break;
    end
    
    if func(lo)*func(mid) < 0
        hi = mid;
    else
        lo = mid;
    end
    iter = iter + 1;
end
 
approx_root = mid;
