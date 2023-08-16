function c = bisection(a,b,eps,f)
a_ = a
b_ = b
c = (a_+b_)/2
while (b_-a_)/2 > eps
    
    fa_to_fc_posorneg = f(a_)*f(c)
    if fa_to_fc_posorneg < 0
        b_ = c
    else
        a_ = c
    end
    c = (a_+b_)/2
    if f(c)==0
        break
    end
end
end