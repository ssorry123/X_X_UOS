#include <stdio.h>
#include <stdlib.h>
#define SIZE 50
#define SWAP(x,y,t) ((t=x),(x=y),(y=t))

int list[SIZE];
int n;

void setArrRandom() {
    int i;
    printf(" something \n");
    for (i = 0; i < SIZE; i++) {
        list[i] = rand() % 10000 + 1;
        printf("%d\t", list[i]);
    }
    printf("\n");
}
int partition(int left, int right) {
    int pivot, temp;
    int low, high;
    low = left;
    high = right + 1;
    pivot = list[left];

    do {
        do {
            low++;
        } while (low <= right && list[low] < pivot);
        do {
            high--;
        } while (high >= left && list[high] > pivot);
        // 
        if (low < high) SWAP(list[low], list[high], temp);
    } while (low < high);

    // 
    SWAP(list[left], list[high], temp);
    return high;
}
void quickSort(int left, int right) {
    if (left < right) {
        int pivot = partition(left, right);
        quickSort(left, pivot - 1);
        quickSort(pivot + 1, right);
    }
}
int main() {
    int i;
    setArrRandom();	
    quickSort(0,SIZE-1);
    printf("���ĵ� �� ����\n");
    for (i = 0; i < SIZE; i++)
        printf("%d\t",list[i]);
    printf("\n");

    return 0;
}