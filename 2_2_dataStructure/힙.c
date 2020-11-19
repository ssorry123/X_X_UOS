#include <stdio.h>
#define qMAX 50
typedef struct {
    int key;
}element;
typedef struct {
    int heap[qMAX+1];
    int heap_size;
}HeapType;
void initHeap(HeapType *h) { h->heap_size = 0; }
void insert_max_heap(HeapType *h, element item) {
    int i = ++(h->heap_size);
    if (h->heap_size > qMAX) { printf("힙꽉참\n"); return; }
    while (i > 1 && h->heap[i / 2] < item.key) {	//부모가 더 작으면
        h->heap[i] = h->heap[i / 2];	//부모의 값을 자식으로 덮어쓴다.
        i = i / 2;	//그리고 한단계 올라간다.
    }
    h->heap[i] = item.key;
}
element delete_max_heap(HeapType *h) {
    element item, temp;
    int parent = 1, child = 2;
    if (h->heap_size == 0) { printf("삭제할 원소 없음\n"); return; }
    item.key = h->heap[1];
    temp.key = h->heap[(h->heap_size)--];
    while (child <= h->heap_size) {
        if ((child < h->heap_size)&& (h->heap[child] < h->heap[child + 1])  ) child++;
        if (h->heap[child] < temp.key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child = parent * 2;	// child = child*2;
    }
    h->heap[parent] = temp.key;
    return item;
}
void heapSort(element a[], int n) {	//정렬할 배열 a와 배열 a의 길이 n;
    int i;
    HeapType hh, *h = &hh;
    initHeap(h);
    for (i = 1; i <= n; i++)
        insert_max_heap(h,a[i]);
    for (i = n; i >=1 ; i--)
        a[i] = delete_max_heap(h);
    // a[]는 정렬되어진다.
}
int main() {
    HeapType hh, *h = &hh;
    element item;
    int z = 1, k;
    initHeap(h);	//heap초기화
    item.key = -1;	//item초기화
    while (z) {
        printf("삽입 = 1, 삭제 = 2, 종료 = 0\t:");
        scanf_s("%d",&k);
        switch(k){
        case 0 :
            z = 0; 
            break;
        case 1: 
            printf("삽입할 원소\t:"); scanf_s("%d",&(item.key));
            insert_max_heap(h,item);
            break;
        case 2:
            item=delete_max_heap(h);
            printf("삭제된 원소 = %d\n",item.key);
            break;
        }
    }
    printf("0000힙에 있는 것으로 정렬 실행\n");
    heapSort(h->heap,h->heap_size);
    for (z = 1; z <= h->heap_size; z++)
        printf("%d ",h->heap[z]);
    printf("종료\n");
}