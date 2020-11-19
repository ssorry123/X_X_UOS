
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrStackType.h"
#define TRUE 1
#define FALSE 0
int check_matching(char *in) {
    StackType *s = (StackType*)malloc(sizeof(StackType));
    char ch, open_ch;
    int i, n = strlen(in);
    init(s);

    for (i = 0; i < n; i++) {
        ch = in[i];
        switch (ch) {
        case '[': case '{': case '(':
            push(s, ch);
            break;
        case ']': case '}': case ')':
            if (is_empty(s))
                return FALSE;
            else {
                open_ch = pop(s);
                if ((open_ch == '(' && ch != ')') || (open_ch == '[' && ch != ']') || (open_ch == '{' && ch != '}'))
                    return FALSE;
                break;
            }
        }
    }
    if (!is_empty(s))
        return FALSE;
    return TRUE;
}
int main() {
    if (check_matching("{ a[(i+1)] = 22 }"))
        printf("A\n");
    else
        printf("B\n");
    return 0;
}
