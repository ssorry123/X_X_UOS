function [N] = InfinityNorm(A)
[R,C]=size(A);
SUMS = zeros(1,R);
for j=1:R
    sum = 0;
    for k=1:C
        sum = sum + abs(A(j,k));
        SUMS(j)=sum;
    end
end
N=max(SUMS);