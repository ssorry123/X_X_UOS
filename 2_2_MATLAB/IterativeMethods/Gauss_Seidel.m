function y = Gauss_Seidel()
% Example 4-8
k=1; x1=0; x2=0; x3=0; x4=0;y=0;
disp(' k           x1         x2        x3         x4')
fprintf('%2.0f      %8.5f   %8.5f   %8.5f   %8.5f   \n',k,x1,x2,x3,x4)
for k=2:8
    x1=(54.5-(-2*x2+3*x3+2*x4))/9;
    x2=(-14-(2*x1-2*x3+3*x4))/8;
    x3=(12.5-(-3*x1+2*x2-4*x4))/11;
    x4=(-21-(-2*x1+3*x2+2*x3))/10;
    fprintf('%2.0f      %8.5f   %8.5f   %8.5f   %8.5f   \n',k,x1,x2,x3,x4)
end