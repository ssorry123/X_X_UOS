#include <stdio.h>
char maze[10][10] = { {1,1,1,1,1,1,1,1,1,1},
                        {'e',0,0,0,1,0,0,0,0,1},
                        {1,0,0,0,1,0,0,0,0,1},
                        {1,0,1,1,1,0,0,1,0,1},
                        {1,0,0,0,1,0,0,1,0,1},
                        {1,0,1,0,1,0,0,1,0,1},
                        {1,0,1,0,1,0,0,1,0,1},
                        {1,0,1,0,1,0,0,1,0,1},
                        {1,0,1,0,0,0,0,1,0,'x'},
                        {1,1,1,1,1,1,1,1,1,1} };
typedef struct {
    int r;
    int c;
}element;
element entry = { 1,0 };
typedef struct Stack {
    element stack[30];
    int top;
}Stack;
void init(Stack *s) {
    s->top = -1;
}
int is_empty(Stack *s) {
    return (s->top == -1);
}
int is_full(Stack *s) {
    return (s->top == 29);
}
void push(Stack *s, int r, int c) {
    element temp;
    temp.r = r;
    temp.c = c;
    if (!is_full(s))
        s->stack[++(s->top)] = temp;
}
element pop(Stack *s) {
    if (!is_empty(s))
        return s->stack[(s->top)--];
}
void push_loc(Stack *s, int r, int c) {
    if (r < 0 || c < 0) return;
    if (maze[r][c] != 1 && maze[r][c] != '.')
        push(s, r, c);
}
void show_maze();
int main() {
    Stack ss;
    element here = entry;
    Stack *s = &ss;
    init(s);
    show_maze();


    while (maze[here.r][here.c] != 'x') {
        //
        int r = here.r;
        int c = here.c;
        maze[r][c] = '.';
        //
        push_loc(s, r - 1, c);
        push_loc(s, r + 1, c);
        push_loc(s, r, c - 1);
        push_loc(s, r, c + 1);
        //	
        if (is_empty(s)) {
            printf("����\n"); return 0;
        }
        else
            here = pop(s);
    }
    printf("����\n");
    show_maze();
    return 0;
}
void show_maze() {
    int i, j;
    printf("\n\t");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n\t");
    }
    printf("\n");
}
