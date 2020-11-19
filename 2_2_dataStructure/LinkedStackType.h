#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef int element;
typedef struct StackNode {
    element item;
    struct StackNode *link;
}StackNode;
typedef struct {
    StackNode *top;
}LinkedStackType;
void init(LinkedStackType *s) {
    s->top = NULL;
}
int is_empty(LinkedStackType *s) {
    return (s->top == NULL);
}
void push(LinkedStackType *s, element item) {
    StackNode *temp = (StackNode*)malloc(sizeof(StackNode));
    if (temp == NULL) { fprintf(stderr, "메모리할당에러\n"); return; }
    else {
        temp->item = item;
        temp->link = s->top;
        s->top = temp;
    }
}
element pop(LinkedStackType *s) {
    if (is_empty(s)) { fprintf(stderr, "스택 공백 에러\n"); exit(1); }
    else {
        StackNode *temp = s->top;
        element ret = temp->item;
        s->top = s->top->link;
        free(temp);
        return ret;
    }
}
element peek(LinkedStackType *s) {
    if (is_empty(s)) { fprintf(stderr, "스택 공백 에러\n"); exit(1); }
    else {
        element ret = s->top->item;
        return ret;
    }
}