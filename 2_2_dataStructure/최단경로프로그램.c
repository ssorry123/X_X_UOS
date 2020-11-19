
#include <stdio.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 8
#define INF 99999
int weight[MAX_VERTICES][MAX_VERTICES] = {
    { INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF },
    { 300,	INF,	INF,	INF,	INF,	INF,	INF,	INF },
    { 100,	800,	INF,	INF,	INF,	INF,	INF,	INF },
    { INF,	INF,	1200,	INF,	INF,	INF,	INF,	INF },
    { INF,	INF,	INF,	1500,	INF,	250,	INF,	INF },
    { INF,	INF,	INF,	1000,	INF,	INF,	900,	1400 },
    { INF,	INF,	INF,	INF,	INF,	INF,	INF,	1000 },
    { 1700,	INF,	INF,	INF,	INF,	INF,	INF,	INF },
};
int found[MAX_VERTICES];
int dist[MAX_VERTICES];
int choose(int n) {
    // 현재 가지 않았고, 갈 수 있는 곳에서
    // 가장 가까운 곳의 위치를 반환.
    int i, min=INF, minpos=-1;
    for (i = 0; i < n; i++)
        if (dist[i] < min && found[i] == FALSE) {
            min = dist[i];
            minpos = i;
        }
    if (minpos == -1) { printf("최소값을 찾을 수 없음.\n"); return; }
    return minpos;
}
void shortestPath(int start, int n) {
    int i, u, w;
    // 초기화
    for (i = 0; i < MAX_VERTICES; i++) {
        found[i] = FALSE;
        dist[i] = weight[start][i];
    }
    // 시작 정점 방문 표시
    found[start] = TRUE;
    dist[start] = 0;
    // 
    for (i = 0; i < n - 2; i++) {	// n-2번만 실행 해도 됨.
        u = choose(n);
        found[u] = TRUE;
        for (w = 0; w < n; w++)
            if (found[w] == FALSE)						// w점을 아직 가지 않았고,
                if (dist[u] + weight[u][w] < dist[w])	// u를 거쳐 w가는 것이 기존 w거리보다 짧은 경우
                    dist[w] = dist[u] + weight[u][w];	// 거리를 더 짧은 것으로 바꾸어 준다.
        
    }
}
int main() {
    int j,M=MAX_VERTICES;
    char city[MAX_VERTICES][20] = { "로스엔젤래스","샌프란시스코","덴버",
    "시카고","보스턴","뉴욕","마이애미","뉴올리언즈"};
        shortestPath(4, M);
        for(j=0;j<M;j++)
            printf("%10s -> %15s >> 최소 거리 = %5d\n", city[4], city[j], dist[j]);
    
}
