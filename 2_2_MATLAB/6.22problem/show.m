function c = show(x,y)
[c,ee]=size(x); %x의 처음과 끝 인덱스 번호 구함
s=x(1);e=x(ee); %x의 처음과 끝 원소 값을 구함
xx=s:0.1:e; %xx 세팅
p=QuadFit(x,y); % p값 구하기
yy=polyval(p,xx);   %yy값 구하기

plot(x,y,'or')  %x,y찍기
hold on
plot(xx,yy,'xb') %xx,yy찍기
end
