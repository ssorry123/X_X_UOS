// 최소힙함수 정의
// 힙원소는 정점 두개와 가중치
#include <stdio.h>
#define MAX 50

typedef struct {
    int key;	//가중치
    int u, v;	//정점 1,2
}element;
typedef struct {
    element heap[MAX + 1];
    int heapSize;
}HeapType;

void initHeap(HeapType *h) {
    h->heapSize = 0;
}
//마지막에 논리적 삽입후 올라가는 함수
void insertMinHeap(HeapType *h, element item) {
    int i = ++(h->heapSize);	//마지막에 논리적 삽입
    if (h->heapSize > MAX) { printf("힙꽉참\n"); return; }
    while (i > 1 && (h->heap[i / 2].key > item.key)) {	//부모가중치가 더 크면
        h->heap[i] = h->heap[i / 2];	//부모값을 자식값으로
        i = i / 2;
    }
    h->heap[i] = item;
}
//마지막것을첫번째에 논리적 삽입후 내려가는 함수
element deleteMinHeap(HeapType *h) {
    element item, temp;
    int parent = 1, child = 2;
    if (h->heapSize == 0) { printf("삭제할원소없음\n"); return; }
    item = h->heap[1];	// return 할 element
    temp = h->heap[(h->heapSize)--]; //논리적으로 맨위로 올라가는 마지막 element
    while (child <= h->heapSize) {
        if ((child < h->heapSize) && (h->heap[child].key > h->heap[child + 1].key))
            child = child + 1;
        if (h->heap[child].key > temp.key) break;	//자식이 더 크면 멈춤.
        //아니면 자식을 하나씩 올려감
        h->heap[parent] = h->heap[child];
        parent = child;
        child = parent * 2;
    }
    //자식이 힙크기를 넘어가서 반복문이 끝났으므로
    //parent 항에 temp를 넣어준다.
    h->heap[parent] = temp;
    return item;
}
