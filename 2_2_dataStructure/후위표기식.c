
#include <stdio.h>
#include <string.h>
#include "arrStackType.h"
int prec(char op);
void infix_to_postfix(char exp[]);
int eval(char exp[]);
int main() {
    char str[] = "82/3-32*+";
    int ans = eval(str);
    printf("정답은 %d\n  ", ans);
    infix_to_postfix("(((8/2)-3)+(3*2))");
    return 0;
}
int prec(char op) {	//연산자의 우선순위 출력, 높을수록 높다.
    switch (op) {
    case '(': case ')':
        return 0;
    case '+': case '-':
        return 1;
    case '*': case '/':
        return 2;
    }
    printf("오류\n");
    return -1;
}
void infix_to_postfix(char exp[]) {	//중위 표기식을 후위 표기식으로 출력
    StackType *s = (StackType*)malloc(sizeof(StackType));
    char ch, top_op;
    int len = strlen(exp), i;
    init(s);
    for (i = 0; i < len; i++) {
        ch = exp[i];
        switch (ch) {
        case '+': case '-': case '*': case '/':
            while (!is_empty(s) && (prec(ch) <= prec(peek(s))))
                printf("%c", pop(s));
            push(s,ch);
            break;
        case '(':
            push(s,ch);
            break;
        case ')':
            top_op = pop(s);
            while (top_op != '(') {
                printf("%c", top_op);
                top_op = pop(s);	//마지막엔 그냥 버려짐 '('
            }
            break;
        default:
            printf("%c", ch);
            break;
        }
    }
    while (!is_empty(s))
        printf("%c", pop(s));
    printf("\n");
}
int eval(char exp[]) {	//후위표기식으로 된 것을 계산
    StackType *s = (StackType*)malloc(sizeof(StackType));
    int op1, op2, value, i;
    int len = strlen(exp);
    char ch;
    init(s);
    for (i = 0; i < len; i++) {
        ch = exp[i];
        if ((ch >= '0' && ch <= '9')) {
            value = ch - '0';
            push(s, value);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            op2 = pop(s);
            op1 = pop(s);
            switch (ch) {
            case '+': push(s, op1 + op2); break;
            case '-': push(s, op1 - op2); break;
            case '*': push(s, op1 * op2); break;
            case '/': push(s, op1 / op2); break;
            }
        }
    }
    value = pop(s);
    return value;
}