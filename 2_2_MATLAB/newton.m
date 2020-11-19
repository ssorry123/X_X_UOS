function y = newton(F,x)
[a,len] = size(x)
ret=zeros(1,len);
for i = 1:len
    ret(i)=F(x(i));
end
y=ret;