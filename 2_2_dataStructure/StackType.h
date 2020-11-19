#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
    element stack[MAX_STACK_SIZE];
    int top;
}StackType;
void init(StackType *s) {	//스택 초기화 함수
    s->top = -1;
}
int is_empty(StackType *s) {
    return (s->top == -1);
}
int is_full(StackType *s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}
void push(StackType *s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n"); return;
    }
    else s->stack[++(s->top)] = item;
}
element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n"); exit(-1);
    }
    else return s->stack[(s->top)--];
}
element peek(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n"); exit(1);
    }
    else return s->stack[s->top];
}