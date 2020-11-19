#pragma once
#include "kvs.h"
#include "skiplist.h"
#include "list.h"
#if (USE==USE_SKIP)
//#define SKIPLIST_MAX_LEVEL 16
//typedef struct snode {
//	int key;
//	int value;
//	struct snode** forward;	// 동적으로 생성한 snode 가리킨다.
//}snode;
//
//typedef struct skiplist {
//	int level;	// 스킵리스트의 현재 (최대)레벨 저장
//	struct snode* header;
//}skiplist;



int rand_level() {
    int level = 1;
    // 레벨 값은 랜덤하게 생성하되
    // level2 확률은 1/2, level3확률은 1/2 * 1/2
    // 단 최대 레벨은 MAX값 미만
    while (flip() == 0 && level < SKIPLIST_MAX_LEVEL) {
        level += 1;
    }

    return level;
}

int flip() {
    // 1/2 확률로 0 또는 1 반환
    return rand() < RAND_MAX / 2;
}

skiplist* skiplist_init(struct KVS_T* kvs){
    int i;
    skiplist* skiplist = &kvs->skiplist;
    // 헤드 노드를 동적으로 만들어 list->header가 참조하도록함
    // key는 가장 큰수로
    snode* header = (snode*)malloc(sizeof(struct snode));
    skiplist->header = header;

    header->key = INT_MAX;
    header->value = INT_MAX;	//	sentinel
    header->forward = (snode**)malloc(sizeof(snode*) * (SKIPLIST_MAX_LEVEL + 1));

    // 모두 헤드노드 참조하도록 초기화
    for (i = 0; i <= SKIPLIST_MAX_LEVEL; i++) {
        header->forward[i] = skiplist->header;
    }
    // 기본 레벨 1
    skiplist->level = 1;

    return skiplist;
}

void skiplist_destroy(struct KVS_T* kvs){
    skiplist* skiplist = &kvs->skiplist;
    snode* current_node = skiplist->header->forward[1];
    while (current_node != skiplist->header) {
        snode* next_node = current_node->forward[1];
        free(current_node->forward);
        free(current_node);
        current_node = next_node;
    }
    // 마지막 정리
    free(skiplist->header->forward);
    free(skiplist->header);
}

void skiplist_allprint(struct KVS_T* kvs) {
    skiplist* list = &kvs->skiplist;
    snode* x = list->header;
    while (x != NULL && x->forward[1] != list->header) {
        x = x->forward[1];
        printf(" [%d, %d] ", x->key, x->value);
    }printf("\n");

    return;
}


int skiplist_put(struct KVS_T* kvs, struct KVS_NODE_T* kv_pair) {
    skiplist* list = &kvs->skiplist;
    snode* update[SKIPLIST_MAX_LEVEL + 1];
    // 새로운 노드를 삽입할 때 삽입할 노드의
    // 레벨이 참조해야 할 노드의 정보를 담고 있음.
    snode* x = list->header, * new_snode;
    int i, level;
    int key = kv_pair->key;
    int value = kv_pair->value;


    // 리스트의 레벨을 감소시키며 forward를 업데이트
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[1];

    // 이미 존재하는 경우
    if (key == x->key) {
        x->value = value;
        return 1;	//found1
    }
    else {
        level = rand_level();
        // 새로운 노드가 생겼을 때 현재 최고 레벨보다
        // 더 큰 레벨일 경우
        if (level > list->level) {
            for (i = list->level + 1; i <= level; i++) {
                update[i] = list->header;
            }
            list->level = level;
        }

        new_snode = (snode*)malloc(sizeof(snode));
        new_snode->key = key;
        new_snode->value = value;
        new_snode->forward = (snode**)malloc(sizeof(snode*) * (level + 1));

        for (i = 1; i <= level; i++) {
            new_snode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_snode;
        }
        return 0;
    }
    
}

struct KVS_NODE_T* skiplist_get(struct KVS_T* kvs, int key) {
    skiplist* list = &kvs->skiplist;
    snode* x = list->header;

    int i;

    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }
    }

    if (x->forward[1]->key == key)
        return x->forward[1];

    return NULL;
}



int skiplist_delete(struct KVS_T* kvs, int key) {
    skiplist* list = &kvs->skiplist;
    int i;
    snode* update[SKIPLIST_MAX_LEVEL + 1];
    snode* x = list->header;

    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[1];
    if (x->key == key) {
        for (i = 1; i <= list->level; i++) {
            if (update[i]->forward[i] != x) {
                break;
            }
            update[i]->forward[i] = x->forward[i];
        }

        if (x) {
            free(x->forward);
            free(x);
        }

        while (list->level > 1 && list->header->forward[list->level] == list->header) {
            list->level--;
        }
        return 1;
    }
    return -1;
}

struct KVS_NODE_T* skiplist_getrange(struct KVS_T* kvs, int start_key, int end_key, int *num_entries, struct KVS_NODE_T* ret ) {
    skiplist* list = &kvs->skiplist;
    snode* x = list->header;
    struct KVS_NODE_T *p_temp_node;
    int key, value;

    while (x != NULL && x->forward[1] != list->header) {
        x = x->forward[1];
        key = x->key;
        value = x->value;
        if (key > end_key) { break; }
        if (key >= start_key && key <= end_key) {
            p_temp_node = (struct KVS_NODE_T*)malloc(sizeof(struct KVS_NODE_T));
            p_temp_node->key = key;
            p_temp_node->value = value;
            list_add(&p_temp_node->list, &ret->list);
            *num_entries += 1;
        }
        
    }

    return ret;
}

#endif