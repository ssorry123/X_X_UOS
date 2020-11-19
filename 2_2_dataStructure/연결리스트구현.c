
#include <stdio.h>
typedef int element;
typedef struct LinkedList{
    element value;
    LinkedList *link;
}LinkedList;

// 
void insert_node(LinkedList **phead, LinkedList *p, LinkedList *new_node) {
    if (*phead == NULL) {
        new_node->link = NULL;
        *phead = new_node;
    }
    else if (p == NULL) {
        new_node->link = *phead;
        *phead = new_node;
    }
    else {
        new_node->link = p->link;
        p->link = new_node;
    }
}
void remove_node(LinkedList **phead, LinkedList *p, LinkedList *node) {
    if (p == NULL)
        *phead = (*phead)->link;
    else
        p->link = node->link;
    free(node);
}
void visit_list(LinkedList *head) {
    LinkedList *p = head;
    while (p != NULL) {
        printf(" %d", p->value);
        p = p->link;
    }
    printf("\n");
}
void visit_list2(LinkedList *head) {
    LinkedList *p = head;
    if (p != NULL) {
        printf(" %d", p->value);
        visit_list2(p->link);
    }
}
LinkedList* find(LinkedList *head, element x) {
    LinkedList *p = head;
    while (p != NULL) {
        if (p->value == x)
            return p;
        p = p->link;
    }
    return p;
}
LinkedList* merge(LinkedList *head1, LinkedList *head2) {
    if (head1 == NULL)
        return head2;
    else if (head2 == NULL)
        return head1;
    else {
        LinkedList *p = head1;
        while (p->link != NULL)
            p = p->link;
        p->link = head2;
        return head1;
    }
}
LinkedList* reverse(LinkedList *head) {
    LinkedList *p, *q, *r;
    p = head;
    q = NULL;
    while (p != NULL) {
        r = q;
        q = p;
        p = p->link;
        q->link = r;
    }
    return q;
}

// 
void insert_first(LinkedList **phead, LinkedList *node) {
    if ((*phead) == NULL) {
        (*phead) = node;
        node->link = node;
    }
    else {
        node->link = (*phead)->link;
        (*phead)->link = node;
    }
}
void insert_last(LinkedList **phead, LinkedList *node) {
    if ((*phead) == NULL) {
        (*phead) = node;
        node->link = node;
    }
    else {
        node->link = (*phead)->link;
        (*phead)->link = node;
        *phead = node;
    }
}
