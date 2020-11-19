function [XS] = RegulaRoot(Fun,a,b,ErrMax)
%xNS1 = before NS
%xNS2 = current NS
%EstimatedRelativeError를 구하기 위해 두개의 NS가 필요하므로
%   0번째 NS는 b로 정해주었다.
imax=100;
Fa = Fun(a); Fb = Fun(b);
if Fa*Fb >0
    disp('에러 : 이 함수는 두 점에서 같은 부호를 가지고 있다.')
else
    disp('iteration  a            b     (xNS)Solution   f(xNS)   EstimatedRelativeError');
    xNS1=b;
    for i=1:imax
        xNS2=(a*Fun(b)-b*Fun(a))/(Fun(b)-Fun(a));   %i번째 NS를 구한다.
        FxNS = Fun(xNS2);   %i번째 NS의 함수값을 구한다.
        Err = abs((xNS2-xNS1)/(xNS1));  %EstimatedRelativeError를 구한다.
        
        %계산 과정 확인용
        fprintf('%3i %11.6f %11.6f %11.6f %11.6f %11.6f\n',i,a,b,xNS2,FxNS,Err)
        
        if FxNS ==0
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
        
        if Fun(a)*Fun(xNS2) <0
            b=xNS2; %TS가 [a,xNS2]에 있다.
        else
            a=xNS2; %TS가 [xNS2,b]에 있다.
        end
        xNS1=xNS2;  %현재 xNS를 이전 xNS로 넣어준다.
    end
end
XS=xNS2;
