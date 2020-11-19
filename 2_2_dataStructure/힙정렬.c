
#include <stdio.h>
#include <malloc.h>
#define heapMAX 50
typedef struct {
    int heap[heapMAX];
    int heap_size;
}Heap;
void initHeap(Heap *h) { h->heap_size = 0; }
void insertMaxHeap(Heap *h, int data) {
    int i = ++(h->heap_size);
    
    while (i > 1) {
        if (h->heap[i / 2] >= data) break;	//부모가 더 크면 탈출.
        h->heap[i] = h->heap[i / 2];	//부모를 자식으로 내림
        i = i / 2;	//한 단계 올라감.
    }
    h->heap[i] = data;
}
int deleteMaxHeap(Heap *h) {
    int parent = 1, child = 2;
    int item, temp;
    item = h->heap[1];	//첫번째 값을 return 할 것임.
    temp = h->heap[(h->heap_size)--];	//마지막 값을 저장해놈.
    while (child <= h->heap_size) {
        // 큰 자식을 선택.
        if (child < h->heap_size && h->heap[child] < h->heap[child + 1]) child++;
        // 선택한 자식보다 temp가 크면 성립하므로 탈출.
        if (temp > h->heap[child]) break;
        // else 선택한 자식과 맨 위로 논리적으로 올라와 있는 temp를 비교.
        h->heap[parent] = h->heap[child];
        parent = child;
        child = parent * 2;	// child = child*2;
    }
    h->heap[parent] = temp;	// 말단에 있던 temp를 물리적으로 저장.
    return item;
}
void heapSort(int arr[], int n) {
    int i;Heap h;
    initHeap(&h);
    //힙에 삽입
    for (i = 1; i <= n; i++) insertMaxHeap(&h, arr[i]);
    //큰것부터 빼면서 정렬
    for (i = n; i >= 1; i--) arr[i] = deleteMaxHeap(&h);
    // 배열의 주소를 받으므로 배열을 정렬된 상태로 덮어쓴다.
}
int main() {
    int n,i,*arr;
    printf("입력할 숫자들의 개수 ? == ");
    scanf_s("%d",&n);
    arr = (int*)malloc(sizeof(int)*n);
    for (i = 1; i <= n; i++) {	//원소를 하나씩 받음.
        printf("  %d번째? == ", i);
        scanf_s("%d", &arr[i]);
    }
    heapSort(arr, n);	// 힙정렬
    for (i = 1; i <= n; i++)
        printf("%d ",arr[i]);	//결과 출력.
    printf("힙정렬 완료\n");return 0;
}
