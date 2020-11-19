#pragma once

// 강의자료와 강의 영상 및
// 추가로 'Park널널한교수' 유튜버 강의 참고

#include <stdlib.h>
#include <stdio.h>
#include "kvs.h"

#if(USE==USE_SKIP)
#define SKIPLIST_MAX_LEVEL 16


typedef struct snode {
    int key;
    int value;
    struct snode** forward;	// 동적으로 생성한 snode 가리킨다.
}snode;

typedef struct skiplist {
    int level;	// 스킵리스트의 현재 (최대)레벨 저장
    struct snode* header;
}skiplist;


/*
skiplist* skiplist_init(skiplist* skiplist);
void skiplist_allprint(skiplist* list);
int skiplist_put(skiplist* list, int key, int value);
snode* skiplist_get(skiplist *list, int key);
void skiplist_destroy(skiplist* list);
int skiplist_delete(skiplist* list, int key);
*/

skiplist* skiplist_init(struct KVS_T *kvs);
void skiplist_destroy(struct KVS_T* kvs);

int skiplist_put(struct KVS_T *kvs, struct KVS_NODE_T *kv_pair);
struct KVS_NODE_T* skiplist_get(struct KVS_T *kvs, int key);
int skiplist_delete(struct KVS_T *kvs, int key);
struct KVS_NODE_T* skiplist_getrange(struct KVS_T* kvs, int start_key, int end_key, int* num_entries, struct KVS_NODE_T* ret);

void skiplist_allprint(struct KVS_T* kvs);

int flip();
int rand_level();

#endif