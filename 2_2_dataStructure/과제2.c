
#include <stdio.h>
int cnt = 0;
int recursive(int n);
double problem15(int n);
int BC(int n, int k);
int BC1(int n, int k);
int main() {
    //recursive(5);
    //printf("%5.6lf",problem15(5));	
    printf("%d\t%d",BC1(20,9),cnt);
    return 0;
}
int recursive(int n) {
    printf("%d\n", n);
    if (n < 1)
        return 2;
    else
        return (2 * recursive(n - 1) + 1);
}
double problem15(int n) {
    //�������
    if (n == 1)
        return 1;
    return (problem15(n - 1) + (double)1/n);
}
int BC(int n, int k) {
    if (n == k || k == 0)
        return 1;
    return BC(n - 1, k - 1) + BC(n - 1, k);
}

int BC1(int n, int k) {
    int i, up, down;
    if (n == k || k == 0)
        return 1;
    if (n - k < k)
        k = n - k;
    up = down = 1;
    for (i = 0; i < k; ++i) {
        up = up * (n-i);
        printf("%d = up\n",up);
        down = down * (i + 1);
        printf("%d = down\n",down);
        if (up%down == 0) {
            cnt++;
            up = up / down;
            down = 1;
            printf("%d = up\n", up);
            printf("down\n\n");
        }
    }
    
    return up / down;
}
