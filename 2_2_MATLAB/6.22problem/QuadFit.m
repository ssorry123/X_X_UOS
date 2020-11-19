function a = QuadFit(x,y)
% x,y 는 row vector 사용
% A=[S1,Sx,Sxx; Sx, Sxx Sxxx; ....]
% x=[a0;a1;a2]  a=[a2, a1, a0]
% b=[Sy;Sxy;Sxxy]
[xR,xC]=size(x);
[yR,yC]=size(y);
if xC~=yC || xR ~=1 || yR ~=1
    disp("error")
    return;
end
% set A
A=zeros(3,3); % A 매트릭스 초기화
N=zeros(1,5); % S1 Sx Sxx Sxxx Sxxxx 저장할 곳
temp1=ones(1,xC); % [1 1 1 1 1]
N(1)=sum(temp1); % [S1 0 0 0 0]
for j=2:5 % set N
    temp1=temp1.*x;
    N(j)=sum(temp1);
end
for j=1:3 %set A
    for k=1:3
        A(j,k)=N(j+k-1);
    end
end
% set b
b=zeros(3,1);   %Sy Sxy Sxxy 저장할 곳
temp2=y;
b(1) = sum(temp2); %[Sy 0 0]
for j=2:3
    temp2=temp2.*x;
    b(j) = sum(temp2);
end
% set x
x=A\b;
% set a
a=zeros(1,3);
for j=1:3
    a(j)=x(4-j);
end
fprintf("best fit is =>\n\t %fx^2 + %fx + %x",a(1),a(2),a(3))