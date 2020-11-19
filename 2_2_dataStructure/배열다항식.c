// 첫번째 방식, 0번째 배열원소 최고차항계수 방식
#include <stdio.h>
#define MAX(a,b) ((a>b)?a:b)
#define MaxDegree 101
typedef struct {
    int degree;	//최고차수
    int coef[MaxDegree];	//항을 저장한다.
}polynomial;
polynomial add(polynomial A, polynomial B);	//폴리노미얼 더하기 함수
int main11() {
    polynomial a = { 5,{3,6,0,0,0,10} };
    polynomial b = { 4,{7,0,5,0,1} };
    polynomial c = add(a, b);
    show_int_array(c.coef,c.degree+1);
    return 0;
}
polynomial add(polynomial A, polynomial B) {
    polynomial C; //정답 저장할 구조체
    int Apos = 0, Bpos = 0, Cpos = 0;	//배열인덱스
    int degreeA = A.degree;	//배열에 넣어줄때마다 감소시키기 위해 만듬
    int degreeB = B.degree;	//왠지 없어도 될거 같지만
    C.degree = MAX(A.degree, B.degree);	//
    while (Apos <= A.degree && Bpos <= B.degree) {	//A와 B의 최고차항까지 둘다 가야 끝남
        if (degreeA > degreeB) {
            C.coef[Cpos++] = A.coef[Apos++];
            --degreeA;
        }
        else if (degreeA == degreeB) {
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
            --degreeA; --degreeB;
        }
        else {
            C.coef[Cpos++] = B.coef[Bpos++];
            --degreeB;
        }
    }
    return C;
}