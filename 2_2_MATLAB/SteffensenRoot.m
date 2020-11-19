function [XS] = SteffensenRoot(Fun,Xest)

imax=100;ErrMax=0.000001;
xNS1=Xest; %첫번째 추정값을 0번째 NS라고 한다.
disp('iteration   xNS         EstimatedRelativeError')
for i=1:imax
    Fx1=Fun(xNS1);
    xNS2=xNS1-(Fx1*Fx1)/(Fun(xNS1+Fx1)-Fx1);   %i번째 NS를 구한다.
    Err=abs((xNS2-xNS1)/xNS1);
    fprintf('%5i   %11.6f   %11.6f\n',i,xNS2,Err)
    
    if Fun(xNS2)==0
        fprintf('정확한 답 = %11.6f',xNS2);
        break
    end
    if Err < ErrMax
        break
    end
    if i==imax
        fprintf('%d번이나 실행했지만 답을 얻을 수 없었다.',imax)
        break
    end
    xNS1=xNS2;  %현재의 NS를 과거의 NS로 바꾼다.
end
XS=xNS2;
