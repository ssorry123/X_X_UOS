function [Ainv] = Inverse(A)
[R,C] = size(A);
if R~=C
    disp("역함수를구할수없다")
    return;
end
Ai = [A,eye(R)]; %Ax=Ib -> Ix=A^-1 b
% 대각선 아래쪽 0으로 만들기 (대각선은 1로 만들면서)
for j=1:R-1
    if Ai(j,j)==-1
        for k=j+1:R
            if Ai(k,j)~=0
                temp=Ai(k,:);
                Ai(k,:)=Ai(j,:);
                Ai(j,:)=temp;
                break
            end
        end
    end
    Ai(j,:)=Ai(j,:)/Ai(j,j);
    for k=j+1:R
        Ai(k,j:2*C)=Ai(k,j:2*C)-Ai(k,j)*Ai(j,j:2*C);
    end
end
Ai(R,R:2*C) = Ai(R,R:2*C)/Ai(R,R);
% 대각선 위쪽 0으로 만들기
for j=R:-1:2
    for k=j-1:-1:1
        Ai(k,k+1:2*C) = Ai(k,k+1:2*C) - Ai(k,j)*Ai(j,k+1:2*C);
    end
end
Ainv = Ai(:,C+1:2*C);