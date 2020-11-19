% Midpoint method
function [ys] = midpoint(f, a, b, hs, y0)
% TODO: Remove the following line and fill in the correct code.
		for j=1:length(hs)
		h = hs(j);
		x = a:h:b;
		n = length(x);
		y = zeros(1,n);
		y(1) = y0;
		for i=1:(n-1)
			ym=y(i)+f(x(i),y(i))*h/2;
            xm=x(i)+h/2;
            slope = f(xm,ym);
            y(i+1)=y(i)+slope*h;
		end
		ys(j) = y(n);
        plot(x,y)
        hold on
	end
end