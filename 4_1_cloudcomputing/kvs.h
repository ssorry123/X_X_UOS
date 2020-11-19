#pragma once
#include <pthread.h>
#include "list.h"
#include "skiplist.h"

#define HASH_MOD 69997


#define USE_LIST 0
#define USE_HASH 1
#define USE_SKIP 2

#define USE 1


struct KVS_T {

    //pthread_mutex_t kv_mu;	// 미사용
    pthread_rwlock_t kv_rw;


#if (USE == USE_LIST)
    struct LIST_HEAD_T list;	
#elif (USE==USE_HASH)
    struct LIST_HEAD_T bk[HASH_MOD];
#elif(USE==USE_SKIP)
    struct skiplist skiplist;
#endif

};

struct KVS_NODE_T {

    int key;
    int value;

    struct LIST_HEAD_T list;

};


// kvs를 만들수 있어야하고 제거할 수 있어야함.
struct KVS_T* kv_create_db();
int kv_destroy_db(struct KVS_T* kvs);

int kv_put(struct KVS_T* kvs, struct KVS_NODE_T* kv_pair);
struct KVS_NODE_T* kv_get(struct KVS_T* kvs, int key);
struct KVS_NODE_T* kv_get_range(struct KVS_T* kvs, int start_key, int end_key, int* num_entries);
int kv_delete(struct KVS_T* kvs, int key);

