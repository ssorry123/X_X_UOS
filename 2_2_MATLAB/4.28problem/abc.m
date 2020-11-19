function yy = abc(xx,F)
yy=zeros(size(xx));
j=1;
for i=0.2:0.1:3
    yy(j)=F(xx(j));
    j=j+1;
end