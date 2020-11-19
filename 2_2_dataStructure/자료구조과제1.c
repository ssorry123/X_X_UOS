
#include <stdio.h>
int arr[100] = { 1,2,3,4,5 };
void insert_array(int loc, int value);
int main() {
    int i;
    insert_array(3, 123, 5);
    for (i = 0; i < 10; i++)
        printf("%d\t", arr[i]);
    printf("\n");

    insert_array(1, 99, 6);
    for (i = 0; i < 10; i++)
        printf("%d\t", arr[i]);
    printf("\n");


    return 0;
}

void insert_array(int loc, int value, int item) {
    int i;
    for (i = item-1; i >= loc; --i)
        arr[i + 1] = arr[i];
    arr[loc] = value;
}
