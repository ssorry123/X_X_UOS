% Modified Euler's method
function [ys] = Euler_modified(f, a, b, hs, y0)
% TODO: Remove the following line and fill in the correct code.
		for j=1:length(hs)
		h = hs(j);
		x = a:h:b;
		n = length(x);
		y = zeros(1,n);
		y(1) = y0;
		for i=1:(n-1)
			slope1 = f(x(i),y(i));
			y(i+1) = y(i) + slope1*h;    %euler
            slope2 = f(x(i+1),y(i+1));
            slope = (slope1+slope2)/2;
            y(i+1) = y(i) + slope*h;
		end
		ys(j) = y(n);
        plot(x,y)
        hold on
        end
    
end
