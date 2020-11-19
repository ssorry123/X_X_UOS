function y = bvp(w1)
x=0:0.001:0.1;
T=zeros(1,101);
w=zeros(1,101);
T(1)=473;   %T(0)
%T(101)=293; %T(0.1)
w(1)=w1;    %w(0)   추정 초기값
h=0.001;    %step size

%dwdx 함수 계싼해놈.
A=166.6667;
B=9.4500e-08;
dwdx = @(k) A*(k-293)+B*(k^4-293^4);

for i=2:101
   T(i)=T(i-1)+w(i-1)*h;             % by explict euler 
   w(i)=w(i-1)+dwdx(T(i-1))*h;       % 
   T(i)=T(i-1)+(w(i-1)+w(i))*h/2;    %modified euler(second RungeKutta)
end
plot(x,T)
hold on
y=T(101);   %초기값을 w1로 했을때 T(0.1)의 값..
