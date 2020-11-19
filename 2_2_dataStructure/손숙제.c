
#include <stdlib.h>
#include <stdio.h>
typedef int element;
typedef struct  ListNode{
    element data;
    struct ListNode *link;
}ListNode;
void show(ListNode *head);
void insert_last(ListNode **phead, element x);
ListNode* alternate(ListNode *headA, ListNode *headB);
int main1() {
    ListNode *A = NULL, *B = NULL, *C;
    int i;
    
    for (i = 0; i < 10; i++)
        insert_last(&A, i);
    show(A);

    for (i = 99; i > 80; i--)
        insert_last(&B, i);
    show(B);

    C = alternate(A, B);
    show(C);
    
    return 0;
}
void show(ListNode *head) {
    ListNode *p = head;
    while (p != NULL) {
        printf("%d  ", p->data); p = p->link;
    }
    printf("\n");
}
void insert_last(ListNode **phead, element x) {
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    temp->link = NULL; temp->data = x;
    if (*phead == NULL) {
        *phead = temp;
    }
    else{
        ListNode *p = *phead;
        while (p->link != NULL)
            p = p->link;
        p->link = temp;
    }
}
ListNode* alternate(ListNode *headA, ListNode *headB) {
    ListNode *headC = NULL, *pa = headA, *pb = headB;
    while (pa != NULL && pb != NULL) {
        insert_last(&headC,pa->data);
        insert_last(&headC,pb->data);
        pa = pa->link;
        pb = pb->link;
    }
    for (; pa != NULL; pa = pa->link)
        insert_last(&headC, pa->data);
    for (; pb != NULL; pb = pb->link)
        insert_last(&headC,pb->data);
    return headC;
}
