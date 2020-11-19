function yy = retyy(xx);
[R,C]=size(xx);
yy=zeros(R,C);
for i=1:C
    yy(i)=mph(xx(i));
end
