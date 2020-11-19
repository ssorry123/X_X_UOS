#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct {
    element data;
    struct ListNode *link;
}ListNode;
typedef struct ListHeader {
    ListNode *head;
    ListNode *tail;
}ListHeader;
void init(ListNode *p) {
    p->data = p->link = NULL;
}
void show(ListNode *head);
void insert_last(ListHeader *plist, element x);
ListNode* alternate(ListHeader *head, ListNode *headB);
int main() {
    ListNode *temp = (ListNode*)malloc(sizeof(ListNode));
    init(temp);
    temp->data = 8;
    printf("hellp");
    free(temp);
    return 0;
}
void insert_last(ListHeader *plist, element x) {
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = x; new_node->link = NULL;
    if (plist->head == NULL) {
        plist->head = new_node;
        plist->tail = new_node;
    }
    else {
        plist->tail = new_node;
    }
}