#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
int avail = 6;
struct {
    float coef;
    int expon;
}terms[MAX_TERMS] = { {8,3},{7,1},{1,0},{10,3},{3,2},{1,0} };
char compare(int a, int b) {	//정수 비교
    if (a > b) return '>';
    else if (a == b) return '=';
    else return '<';
}
void attach(float coef, int expon) {	//새로운 항을 결과 다항식에 추가
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "항의 개수가 너무 많음\n");
        exit(1);
    }
    terms[avail].coef = coef;
    terms[avail++].expon = expon;
}
void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce) {
    float tempCoef;	//임시 Coef값
    *Cs = avail;	//Cs의 값을 avail로 바꾼다
    while (As <= Ae && Bs <= Be) {
        switch (compare(terms[As].expon, terms[Bs].expon)) {
        case '>':
            printf(">\n");
            attach(terms[As].coef, terms[As].expon);
            As++;
            break;
        case '=':
            printf("=\n");
            tempCoef = terms[As].coef + terms[Bs].coef;
            attach(tempCoef, terms[As].expon);
            As++; Bs++;
            break;
        case '<':
            printf("<\n");
            attach(terms[Bs].coef, terms[Bs].expon);
            Bs++;
            break;
        }
    }
        for (; As <= Ae; As++)
            attach(terms[As].coef, terms[Ae].expon);
        for (; Bs <= Be; Bs++)
            attach(terms[Bs].coef, terms[Be].expon);
        *Ce = avail - 1;
    
}
int main11() {
    int Cs, Ce;
    
    poly_add2(0, 2, 3, 5, &Cs, &Ce);
    
    for(;Cs<=Ce;Cs++)
        printf(" + %.1fx^%d",terms[Cs].coef,terms[Cs].expon);
    
    return 0;
}