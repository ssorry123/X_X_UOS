% 4th order Runge-Kutta method (classical)
function [ys] = RK4_classical(f, a, b, hs, y0)
% TODO: Remove the following line and fill in the correct code.
		for j=1:length(hs)
		h = hs(j);
		x = a:h:b;
		n = length(x);
		y = zeros(1,n);
		y(1) = y0;
		for i=1:(n-1)
			K1=f(x(i),y(i));
            K2=f(x(i)+h/2,y(i)+K1*h/2);
            K3=f(x(i)+h/2,y(i)+K2*h/2);
            K4=f(x(i)+h,y(i)+K3*h);
            y(i+1)=y(i)+(K1+2*K2+2*K3+K4)*h/6;
		end
		ys(j) = y(n);
        plot(x,y)
        hold on
	end
end
