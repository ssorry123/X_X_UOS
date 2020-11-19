#include <stdio.h>
#include "union_find.h"
#include "minHeap.h"
void insert_heap_edge(HeapType *h, int u, int v, int weight) {
    element e;
    e.key = weight;
    e.u = u;
    e.v = v;
    insertMinHeap(h, e);
}
void insertAllEdges(HeapType *h);
void kruskal(int n) {
    int edgeAccepted = 0;
    HeapType hh, *h=&hh;
    int uset, vset;
    element e;
    initHeap(h);			//힙초기화
    insertAllEdges(h);	//힙에 모든 edge삽입
    set_init(n);
    while (edgeAccepted < (n - 1)) {	// n-1개의 간선을 연결한다.
        e = deleteMinHeap(h);	//가장 작은 가중치 간선 하나 뺀다.
        uset = set_find(e.u);	//이 과정에서 같은 그룹의 정점들은
        vset = set_find(e.v);	//모두 부모가 같아진다.
        printf("\t%d'set=%d,  %d'set=%d\n",e.u,uset,e.v,vset);
        if (uset != vset) {
            printf("( %d , %d ) %d \n",e.u,e.v,e.key);
            edgeAccepted++;
            set_union(uset,vset);
        }
    }
}
int main() {
    kruskal(7);
    return 0;
}
void insertAllEdges(HeapType *h) {
    insert_heap_edge(h, 0, 1, 29);
    insert_heap_edge(h, 1, 2, 16);
    insert_heap_edge(h, 2, 3, 12);
    insert_heap_edge(h, 3, 4, 22);
    insert_heap_edge(h, 4, 5, 27);
    insert_heap_edge(h, 5, 0, 10);
    insert_heap_edge(h, 6, 1, 15);
    insert_heap_edge(h, 6, 3, 18);
    insert_heap_edge(h, 6, 4, 25);
}