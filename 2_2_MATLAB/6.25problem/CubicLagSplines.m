function Yint = CubicLagSplines(x,y,xint)
[xR,xC]=size(x);
[yR,yC]=size(y);
N=xC;
if xC ~= yC || xR ~= 1 || yR ~= 1
    disp("오류");return;
end
% h set , h는 1부터 N-1까지 있다.
h=zeros(1,N-1);
for j=1:N-1
    h(j)=x(j+1)-x(j);
end
% a set with A, b
A=zeros(N-2,N-2);
b=zeros(N-2,1);
A(1,1)=2*(h(1)+h(2));
A(1,2)=h(2);
A(N-2,N-3)=h(N-2);
A(N-2,N-2)=2*(h(N-2)+h(N-1));
for j=2:N-3 %set A
    A(j,j-1)=h(j);
    A(j,j)=2*(h(j)+h(j+1));
    A(j,j+1)=h(j+1);
end
for j=1:N-2 %set B
    b(j)=6*( (y(j+2)-y(j+1))/h(j+1) - (y(j+1)-y(j))/h(j) );
end
atemp=A\b;
a=zeros(N,1);   % a는 1부터 N까지
a(2:N-1,1)=atemp(:,1);
% xint가 첫번째와 마지막 구간이 아닌 경우
%   ->3차다항식 이용
% xint가 첫번째와 마지막 구간을 지나는 경우
%   ->3점을 지나는 2차 다항식 사용
[c,cnt]=size(xint);
YY=zeros(1,cnt);
for k=1:cnt
    i=-1;
    for j=1:N-1 % xint(k)가 j구간에 있으면 i=j 후 break
        xx=xint(k);
        if xx>=x(j) && xx<=x(j+1)
            i=j;
            break
        end
    end
    if i==-1    % xx가 구간에 없으면 오류 종료
        disp("오류");return
    end
    if i==1 || i==N-1
        YY(k)= QuadraticSplines(i,x,y,N,xx);
        continue
    end
    YY(k)=a(i) * (x(i+1)-xx)^3 / (6*h(i)) + a(i+1) * (xx-x(i))^3 / (6*h(i)) + (y(i)/h(i) - a(i)*h(i)/6) * (x(i+1) - xx) + (y(i+1)/h(i) - a(i+1)*h(i)/6) * (xx-x(i));
end
Yint=YY;
end
function y = QuadraticSplines(i,x,y,N,xx)
A=ones(3,3);
b=zeros(3,1);
ci = i;
if i==1
    for j=1:3
        b(j)=y(j);
        for k=1:2
            A(j,k)=x(ci)^(3-k);
        end
        ci=ci+1;
    end
elseif i==N-1
    ci=N-2;
    for j=1:3
        b(j)=y(ci);
        for k=1:2
            A(j,k)=x(ci)^(3-k);
        end
        ci=ci+1;
    end
end
p=A\b;
y=polyval(p,xx);
end