
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define qMAX 50
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;
typedef struct {
    int *arr;	
    int *cache;	
    int arrLength;
}A;
typedef struct {
    TreeNode *data[qMAX];
    int front, rear;
}Queue;
void initQueue(Queue *q) {
    q->front = q->rear = 0;
}
void pushQ(Queue *q, TreeNode *t) {
    if ((q->front) == (q->rear + 1) % qMAX) { printf("����"); return 1; }
    q->data[++(q->rear)] = t;
}
TreeNode *popQ(Queue *q) {
    if (q->front == q->rear) { printf("�����"); return 1; }
    return q->data[++(q->front)];
}
A* makeArr(TreeNode *t) {
    int h = heightTree(t), i;
    int arrLength = (int)pow(2, h); // [1, arrLength-1]
    A *a = (A*)malloc(sizeof(A));
    a->arr = (int*)malloc(sizeof(int)*arrLength);
    a->cache = (int*)malloc(sizeof(int)*arrLength);
    a->arrLength = arrLength;
    for (i = 0; i < arrLength; i++) {
        a->arr[i] = a->cache[i] = 0;
    }
    a->cache[0] = -1; 
    return a;
}
int heightTree(TreeNode *t) {
    int h, a, b;
    if (t == NULL) return 0;
    h = (a = heightTree(t->left)) > (b = heightTree(t->right)) ? a : b;
    return h + 1;
}

int findLeastAbleIndex(A *a) {
    int i = 1, ret;
    for (i = 1; i < a->arrLength; i++)
        if (a->cache[i] != -1)
            break;
    a->cache[i] = -1;	
    return i;
}
void toCacheminusOne(A *a, int i) {
    if (i > a->arrLength) return;
    a->cache[i] = -1;
    a->arr[i] = -1;
    toCacheminusOne(a, 2 * i);
    toCacheminusOne(a, 2 * i + 1);
}
A* levelTree(TreeNode *t) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    A *a = makeArr(t);
    initQueue(q);
    pushQ(q, t);
    while (!(q->rear == q->front)) {
        TreeNode *x = popQ(q);
        int i;
        if (x != NULL) { printf("%d ", x->data); a->arr[(i = findLeastAbleIndex(a))] = x->data; }

        if (x->left != NULL)
            pushQ(q, x->left);
        else
            toCacheminusOne(a, 2 * i);

        if (x->right != NULL)
            pushQ(q, x->right);
        else
            toCacheminusOne(a, 2 * i + 1);
    }
    printf("\n");
    return a;
}

int main() {
    TreeNode n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;	//n1 = root node
    A *a; int i;
    n1.data = 8; n1.left = &n2; n1.right = &n3;
    n2.data = 5; n2.left = &n4; n2.right = &n5;
    n3.data = 4; n3.left = NULL; n3.right = &n6;
    n4.data = 9; n4.left = NULL; n4.right = NULL;
    n5.data = 7; n5.left = &n7; n5.right = &n8;
    n6.data = 11; n6.left = &n9; n6.right = NULL;
    n7.data = 1; n7.left = NULL; n7.right = NULL;
    n8.data = 12; n8.left = &n10; n8.right = NULL;
    n9.data = 3; n9.left = NULL; n9.right = NULL;
    n10.data = 2; n10.left = NULL; n10.right = NULL;

    a=levelTree(&n1);
    
}
