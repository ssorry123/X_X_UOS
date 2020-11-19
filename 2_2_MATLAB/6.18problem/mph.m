function y= mph(x)
if x>=14 && x<=22
    y=f1(x);return;
end
if x>=22 && x<=30
    y=f2(x);return;
end
if x>=30 && x<=38
    y=f3(x);return;
end
if x>=38 && x<=46
    y=f4(x);return;
end
disp("범위오류")
y=-1;


