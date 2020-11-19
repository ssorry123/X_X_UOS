
#include <stdio.h>
#include <math.h>
void hanoi(int n, int a, int b, int c);
int main11() {
    int arr[1000000];
    int input;
    scanf_s("%d", &input);
    printf("%d\n", (int)pow(2,input)-1);
    hanoi(input, 1, 2, 3);
    
    return 0;
}
void hanoi(int n, int a, int b, int c) {
    
    if (n == 1){
        printf("%d %d\n", a, c);
        return;
    }

    hanoi(n - 1, a, c, b);
    printf("%d %d\n", a, c);
    hanoi(n - 1, b, a, c);
}
