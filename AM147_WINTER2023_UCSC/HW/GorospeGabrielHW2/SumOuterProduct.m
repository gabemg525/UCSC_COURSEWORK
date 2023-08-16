function s = SumOuterProduct(x)
X = x*transpose(x)
s = 0

for i = 1:size(x)
    r = X(i,i:end)
    s = s + sum(r)
end
end