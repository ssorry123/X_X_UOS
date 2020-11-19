function x = GaussPivotLarge(A,b)
Ab=[A,b];   %증강매트릭스
[ROWS, COLS] = size(Ab);
for j=1:ROWS-1
    if Ab(j,j)==0   %피봇 위치에 0이면 row exchange하기
        for k=j+1:ROWS
            if Ab(k,j) ~= 0
                AbTemp = Ab(j,:);
                Ab(j,:) = Ab(k,:);
                Ab(k,:) = AbTemp;
                break;
            end
        end
    end
    Large = abs(Ab(j,j));    %j번째 column중 절대값이 가장 큰 값으로 exchange하기
    for k=j+1:ROWS
        if abs(Ab(k,j))>Large
            Large = abs(Ab(k,j));
            AbTemp = Ab(j,:);
            Ab(j,:) = Ab(k,:);
            Ab(k,:) = AbTemp;
        end
    end
    for i=j+1:ROWS      %Gauss Elimination
        Ab(i,j:COLS) = Ab(i,j:COLS) - Ab(i,j)/Ab(j,j)*Ab(j,j:COLS);
    end
    %back substitution 으로 solution 구하기
    x=zeros(ROWS,1);
    x(ROWS)=Ab(ROWS,COLS)/Ab(ROWS,ROWS);    %처음으로 구한 solution
    for i= ROWS-1:-1:1
        x(i)= ( Ab(i,COLS)-Ab(i,i+1:ROWS)*x(i+1:ROWS) ) / Ab(i,i);
    end
end
