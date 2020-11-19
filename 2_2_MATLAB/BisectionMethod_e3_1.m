clear all
F=@(x) 8-4.5*(x-sin(x));
a=2;b=3;imax=20;tol=0.001;
Fa=F(a);Fb=F(b);
if Fa*Fb >0
    disp('Error:The function has the same sign at points a and b.')
else
    disp('iteration a b (xNS) Solution f(xNS) Tolerance')
    for i=1:imax
        xNS = (a+b)/2;
        toli = (b-a)/2;
        FxNS = F(xNS);
        fprintf('%3i %11.6f %11.6f %11.6f %11.6f %11.6f\n',i,a,b,xNS,FxNS,toli)
        if FxNS == 0
            fprintf('An exact solution x = %11.6f was found',xNS)
            break
        end
        if toli<tol
            break
        end
        if i==imax
            fprintf('Solution was not obtained in %i iterations',imax)
            break
        end
        if FxNS <0
            b=xNS;
        else
            a=xNS;
        end
    end
end