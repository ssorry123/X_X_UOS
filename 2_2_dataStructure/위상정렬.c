
#include <stdio.h>
#include "StackType.h"
#define N 6
int arr[N][N] = {
    {0,0,1,1,0,0},
    {0,0,0,1,1,0},
    {0,0,0,1,0,1},
    {0,0,0,0,0,1},
    {0,0,0,0,0,0}
};
int inDegree[N];

void topoSort() {
    int i, j;
    StackType stack,*s=&stack;
    int inDegree[N];
    for (i = 0; i < N; i++) inDegree[i] = 0; // 
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (arr[j][i] !=0)
                inDegree[i]++;
    init(s);
    for (i = 0; i < N; i++)
        if (inDegree[i] == 0)
            push(s,i);

    if (is_empty(s)) { printf("fail\n"); return; }


    while (!is_empty(s)) {
        int w = pop(s);
        printf("%3d\t",w);
        for (i = 0; i < N; i++)
            if (arr[w][i] != 0)
                if ((--inDegree[i]) == 0)
                    push(s,i);
    }

    
    return;

}
main() {
    topoSort();
}
