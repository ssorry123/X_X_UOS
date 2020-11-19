#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#define MAX_TERMS 20
typedef struct {
    int loc_row;	//요소의 행위치
    int loc_col;	//요소의 열위치
    int value;		//요소의 값
}element;
typedef struct SparseMatrix {
    element data[MAX_TERMS];
    int terms;		// 0이 아닌 요소의 개수
    int rows;		// 행의 개수
    int cols;		// 열의 개수
}SparseMatrix;
SparseMatrix add2(SparseMatrix a, SparseMatrix b);
void showMatrix(SparseMatrix c);
void showMatrix2(SparseMatrix c);
int main() {
    SparseMatrix m[2]; int i, j;
    clock_t start, finish;
    // 두 행렬의 요소를 설정한다
    for (i = 0; i < 2; i++) {
        SparseMatrix* SM = &m[i];
        printf("^^  %d번째행렬의 행과 열 입력  :  ", i);
        scanf_s("%d %d", &(SM->rows), &(SM->cols));
        printf("^^  %d번째행렬의 요소의 개수를 입력하세요 :  ", i);
        scanf_s("%d", &(SM->terms));
        printf("^^  요소의 row와 col, value을 입력하세요 : \n");
        for (j = 0; j < SM->terms; ++j) {
            element* e = &(SM->data[j]);
            printf("%d번째 요소 : ", j);
            scanf_s("%d %d %d", &(e->loc_row), &(e->loc_col), &(e->value));
        }
    }
    // 두 행렬을 더하는 함수를 호출한다
    SparseMatrix c = add2(m[0], m[1]);
    // 두 행렬을 더한 결과를 출력한다
    start = clock();
    showMatrix(c);
    finish = clock();
    printf("%.8lf\n",(double)(finish-start)/CLOCKS_PER_SEC);
    start = clock();
    showMatrix2(c);
    finish = clock();
    printf("%.8lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
    return 0;
}
SparseMatrix add2(SparseMatrix a, SparseMatrix b) {
    SparseMatrix c;
    int ca = 0, cb = 0, cc = 0;
    if (a.rows != b.rows || a.cols != b.cols) {	//크기가 다르면 종료
        fprintf(stderr, "희소행렬 크기 에러!\n"); exit(1);
    }
    // c의 행과 열 설정
    c.rows = a.rows;
    c.cols = a.cols;
    while (ca < a.terms && cb < b.terms) {
        // 각 요소의 순차적인 번호 계산
        int inda = a.data[ca].loc_row*a.cols + a.data[ca].loc_col;
        int indb = b.data[cb].loc_row*b.cols + b.data[cb].loc_col;
        // 순차적인 번호에 따라 계산
        if (inda < indb)
            c.data[cc++] = a.data[ca++];
        else if (inda == indb) {
            if ((a.data[ca].value + b.data[cb].value)) {
                c.data[cc] = a.data[ca];	// 위치,값을 덮고 값을 다시 덮는다.
                c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
            }
            else {
                ca++; cb++;
            }
        }
        else
            c.data[cc++] = b.data[cb++];
    }
    //남아있는 요소들을 모두 옮긴다.
    for (; ca < a.terms;)
        c.data[cc++] = a.data[ca++];
    for (; cb < b.terms;)
        c.data[cc++] = b.data[cb++];
    // c의 요소의 개수를 적어준다.
    c.terms = cc;
    // c를 반환한다.
    return c;
}
void showMatrix(SparseMatrix c) {
    int N = c.cols*c.rows, i;	// c행렬의 전체 항의 개수, 반복자
    int linear[10000] = { 0 };	// c행렬의 값을 선형으로 저장할 공간
    // linear[c의 요소의 선형 좌표]:=c의 요소 값;
    for (i = 0; i < c.terms; i++)
        linear[c.cols*c.data[i].loc_row + c.data[i].loc_col] = c.data[i].value;
    // cols마다 줄바꿈하며 하나씩 출력한다.
    printf("\n_____________________\n\n");
    for (i = 0; i < N; i++) {
        printf("%3d", linear[i]);
        if ((i + 1) % c.cols == 0)
            printf("\n");
    }
    printf("_____________________\n");
}
void showMatrix2(SparseMatrix c) {
    int j, k, i = 0;
    printf("\n_____________________\n\n");
    for (j = 0; j < c.rows; j++) {
        for (k = 0; k < c.cols; k++) {
            element* e = &(c.data[i]);
            if (j == e->loc_row && k == e->loc_col) {
                printf("%3d", e->value);
                i++;
            }
            else
                printf("%3d", 0);
        }
        printf("\n");
    }
    printf("_____________________\n");
}
