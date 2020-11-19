
#include <stdio.h>
#include <malloc.h>
#include <math.h>
typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;
TreeNode *search1(TreeNode *node, int key) {	//순환적인 탐색 방법
    if (node == NULL)	return NULL;
    if (node->key == key) return node;
    if (node->key < key) return search1(node->right, key);
    else return search1(node->left, key);
}
TreeNode *search2(TreeNode *node, int key) {	//반복적인 탐색 방법
    while (node != NULL) {
        if (node->key == key) return node;
        if (node->key < key) node = node->right;
        else node = node->left;
    }
    return NULL;
}
void insert_node(TreeNode **root, int key) {
    TreeNode *p = NULL, *t = *root, *n;
    // 단말노드까지 탐색
    while (t != NULL) {
        p = t;
        if (t->key == key)	return;	//이미 있는 경우 삽입하지 않음.
        if (t->key < key) t = t->right;
        else t = t->left;
    }
    // 노드 생성
    n = (TreeNode*)malloc(sizeof(TreeNode));
    n->right = n->left = NULL;
    n->key = key;
    if (p == NULL)
        *root = n;
    else
        if (p->key < key)	p->right = n;
        else	p->left = n;
}
void delete_node(TreeNode **root, int key) {
    TreeNode *t = *root, *p = NULL, *child = NULL, *succ = NULL, *succ_p = NULL;
    while (t != NULL && t->key != key) {	//삭제할 노드 t를 찾는다.
        p = t;
        t = (key > t->key) ? t->right : t->left;
    }
    if (t == NULL) { printf("삭제할노드가없음\n"); return; }
    if (t->left == NULL && t->right == NULL) {	//t의 자식이 없음
        if (p != NULL) {
            if (p->right == t) p->right = NULL;
            else p->left = NULL;
        }
        else *root = NULL;
    }
    else if (t->left == NULL || t->right == NULL) {
        child = (t->left != NULL) ? t->left : t->right;
        if (p != NULL) {
            if (p->right == t) p->right = child;
            else p->left = child;
        }
        else *root = child;
    }
    else {
        succ_p = t;
        succ = t->right;	//오른쪽서브트리에서 후속자를 찾는다.
        while (succ->left != NULL) {
            succ_p = succ;
            succ = succ->left;
        }
        //후속자의 후손들을 후속자의 부모로 옮긴다.
        if (succ_p->right == succ)	//위의 while문을 한번도 하지 않았다면 가능
            succ_p->right = succ->right;	//후속자의 자녀는 없거나 오른쪽만 있다.
        else succ_p->left = succ->right;	//보통의 경우
        //삭제할 노드를 후속자로 덮어 씌운다.
        t->key = succ->key;
        //후속자노드를 삭제한다.
        t = succ;
    }
    free(t);	//연결을 끊은후 t들을 모두 반납
}
int get_height(TreeNode *root) {
    int level = 0, a, b;
    if (root == NULL) return level;
    level = (a = get_height(root->left)) > (b = get_height(root->right)) ? a : b;
    return level + 1;
}
void showTree(TreeNode *root) {	//트리모양처럼 출력해보자.
    int level = get_height(root);
    int maxIndex = (int)pow(2, level) - 1;
    int *arr = (int*)malloc(sizeof(int)*maxIndex);
    int i = 0, lev = 1;
}
int main() {
    TreeNode n1, n2, n3, n4, n5, n6, n7;	//n1 = root node
    n1.key = 8; n1.left = &n2; n1.right = &n3;
    n2.key = 5; n2.left = &n4; n2.right = &n5;
    n3.key = 4; n3.left = NULL; n3.right = &n6;
    n4.key = 9; n4.left = NULL; n4.right = NULL;
    n5.key = 7; n5.left = NULL; n5.right = NULL;
    n6.key = 11; n6.left = &n7; n6.right = NULL;
    n7.key = 3; n7.left = NULL; n7.right = NULL;
    showTree(&n1);
}
