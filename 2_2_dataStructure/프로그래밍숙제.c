
#include <stdio.h>
#include <stdlib.h>
typedef struct ListNode {
    int coef;
    int expon;
    struct ListNode *link;
}ListNode;
typedef struct ListHeader {
    int length;
    ListNode *head;
    ListNode *tail;
}ListHeader;
void init(ListHeader *plist) {
    plist->length = 0;
    plist->head = plist->tail = NULL;
}
void insert_node_last(ListHeader *plist, int coef, int expon) {
    ListNode *temp = (ListNode*)malloc(sizeof(ListNode));
    if (temp == NULL) perror("�޸��Ҵ翡��");
    temp->coef = coef; temp->expon = expon; temp->link = NULL;
    if (plist->tail == NULL)
        plist->head = plist->tail = temp;
    else {
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->length++;
}
void poly_add(ListHeader *plist1, ListHeader *plist2, ListHeader *plist3) {
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;
    int sum;
    while (a != NULL && b != NULL) {
        if (a->expon == b->expon) {
            sum = a->coef + b->coef;
            if (sum != 0) insert_node_last(plist3,sum,a->expon);
            a = a->link; b = b->link;
        }
        else if (a->expon > b->expon) {
            insert_node_last(plist3, a->coef, a->expon);
            a = a->link;
        }
        else {
            insert_node_last(plist3, b->coef, b->expon);
            b = b->link;
        }
    }
    for (; a != NULL; a = a->link)
        insert_node_last(plist3, a->coef, a->expon);
    for (; b != NULL; b = b->link)
        insert_node_last(plist3, b->coef, b->expon);
}
void poly_printf(ListHeader *plist) {
    ListNode *p = plist->head;
    for (; p!=NULL; p = p->link)
        printf("%d %d\n", p->coef, p->expon);
}
int main() {
    ListHeader l1, l2, l3;
    init(&l1); init(&l2); init(&l3);
    insert_node_last(&l1, 3, 6); insert_node_last(&l1, 7, 3);
    insert_node_last(&l1, -2, 2); insert_node_last(&l1, -9, 0);

    insert_node_last(&l2, -2, 6); insert_node_last(&l2, -4, 4);
    insert_node_last(&l2, 6, 2); insert_node_last(&l2, 6, 1);
    insert_node_last(&l2, 1, 0);

    poly_add(&l1, &l2, &l3);
    poly_printf(&l3);
    return 0;
}
