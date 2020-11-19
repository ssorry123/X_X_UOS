#include <stdio.h>
#define MAX_VERTICES 100
#define INF 1000
int parent[MAX_VERTICES];	// 노드의 부모노드를 저장
int num[MAX_VERTICES];		//해당 집합의 크기 저장
void set_init(int n) {
    int i;
    for (i = 0; i < n; i++) {
        parent[i] = -1;
        num[i] = 1;
    }
}
// 하나의 부모가 같은 그룹의 정점을 모두 자식으로 가지게 한다.
int set_find(int vertex) {
    int p, s, i = -1;
    // 인자로 들어온 vertex의 부모를 찾는다.
    for (i = vertex; (p = parent[i]) >= 0; i = p);
    s = i; // 찾은 부모를 대표원소로 한다.
    // 찾은 부모의 모든 자식들의 부모를 찾은 부모(대표원소)로 바꾼다.
    for (i = vertex; (p = parent[i]) >= 0; i = p)
        parent[i] = s;
    
    return s;	//찾은 부모 반환.
}
void set_union(int s1, int s2) {
    if (num[s1] < num[s2]) {	//s2가 속한 집합이 더 크면
        parent[s1] = s2;	// s1의 부모는 s2가 되고
        num[s2] += num[s1];	// s2가 속한 집합의 개수는 커진다.
    }
    else {
        parent[s2] = s1;
        num[s1] += num[s2];
    }
}