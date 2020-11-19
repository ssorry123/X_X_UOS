#pragma once
#include "kvs.h"
#include "skiplist.h"

struct KVS_T* kv_create_db() {
    struct KVS_T* cc_kvs;
    int i;

    // 할당
    cc_kvs = (struct KVS_T*)malloc(sizeof(struct KVS_T));
    if (cc_kvs == NULL)
        return NULL;

    // 초기화
#if(USE==USE_LIST)
    init_list_head(&cc_kvs->list);	//리스트 초기화
#elif(USE==USE_HASH)
    for (i = 0; i < HASH_MOD; i++) {
        init_list_head(&cc_kvs->bk[i]);	// 해쉬 초기화
    }
#elif(USE==USE_SKIP)
    skiplist_init(cc_kvs);
#endif


    // 락변수 초기화
    //cc_kvs->kv_mu = PTHREAD_MUTEX_INITIALIZER;
    cc_kvs->kv_rw = PTHREAD_RWLOCK_INITIALIZER;

    return cc_kvs;
};


int kv_destroy_db(struct KVS_T* kvs) {
    struct LIST_HEAD_T* p_entry, * tmp;
    struct KVS_NODE_T* p_kvs_node;
    int i;

    if (kvs == NULL)
        return -1;

#if(USE==USE_LIST)
    list_for_each_safe(p_entry, tmp, &kvs->list) {
        p_kvs_node = list_entry(p_entry, struct KVS_NODE_T, list);
        list_del(&p_kvs_node->list);	// 삭제
        free(p_kvs_node);		// 메모리 해제
    }
#elif(USE==USE_HASH)
    for (i = 0; i < HASH_MOD; i++) {
        list_for_each_safe(p_entry, tmp, &kvs->bk[i]) {
            p_kvs_node = list_entry(p_entry, struct KVS_NODE_T, list);
            list_del(&p_kvs_node->list);	// 삭제
            free(p_kvs_node);		// 메모리 해제
        }
    }
#elif(USE==USE_SKIP)
    skiplist_destroy(kvs);
#endif

    free(kvs);

    return 0;
};

int kv_put(struct KVS_T* kvs, struct KVS_NODE_T* kv_pair) {
    struct LIST_HEAD_T* p_entry;
    struct KVS_NODE_T* p_kvs_node;
    int found = 0;
    int bk_key;
    if (kvs == NULL)
        return -1;


    pthread_rwlock_wrlock(&kvs->kv_rw);

    // 1. 키가 이미 존재하는지 확인
    struct LIST_HEAD_T* temp;
#if(USE==USE_LIST)
    temp = &kvs->list;
#elif(USE==USE_HASH)
    bk_key = (kv_pair->key) % HASH_MOD;
    temp = &kvs->bk[bk_key];
#endif
#if((USE==USE_LIST)||(USE==USE_HASH))
    list_for_each(p_entry, temp) {
        p_kvs_node = list_entry(p_entry, struct KVS_NODE_T, list);
        // 키가 중복된다면 값을 치환
        if (p_kvs_node->key == kv_pair->key) {
            found = 1;
            p_kvs_node->value = kv_pair->value;
            break;
        }
    }
    // 키가 중복되지 않는다면 새로 만들고 삽입
    if (!found) {
        p_kvs_node = (struct KVS_NODE_T*)malloc(sizeof(struct KVS_NODE_T));
        p_kvs_node->key = kv_pair->key;
        p_kvs_node->value = kv_pair->value;
        init_list_head(&p_kvs_node->list);
        list_add(&p_kvs_node->list, temp);
    }
#endif


#if(USE==USE_SKIP)
    // 이미 존재하는지 확인하는 부분은 skiplist에 구현되어있다.
    found = skiplist_put(kvs, kv_pair);
#endif

    pthread_rwlock_unlock(&kvs->kv_rw);
    return found;
}

struct KVS_NODE_T* kv_get(struct KVS_T* kvs, int key) {
    struct LIST_HEAD_T* p_entry;
    struct KVS_NODE_T* p_kvs_node = NULL, * ret = NULL;
    int found = 0;
    int bk_key;
    if (kvs == NULL)
        return -1;


    ret = (struct KVS_NODE_T*)malloc(sizeof(struct KVS_NODE_T));
    if (ret == NULL)
        return NULL;

    pthread_rwlock_rdlock(&kvs->kv_rw);

    struct LIST_HEAD_T* temp;
#if(USE==USE_LIST)
    temp = &kvs->list;
#elif(USE==USE_HASH)
    bk_key = key % HASH_MOD;
    temp = &kvs->bk[bk_key];
#endif
#if((USE==USE_LIST)||(USE==USE_HASH))
    list_for_each(p_entry, temp) {
        p_kvs_node = list_entry(p_entry, struct KVS_NODE_T, list);
        // 키가 중복된다면, 찾았다면
        if (p_kvs_node->key == key) {
            found = 1;
            break;
        }
    }

    if (found) { // 메모리 복사후 리턴
        memcpy((void*)ret, (void*)p_kvs_node, sizeof(struct KVS_NODE_T));
        pthread_rwlock_unlock(&kvs->kv_rw);
        return ret;
    }
    else {
        pthread_rwlock_unlock(&kvs->kv_rw);
        return NULL;
    }
#endif



#if(USE==USE_SKIP)
    ret = skiplist_get(kvs, key);
    pthread_rwlock_unlock(&kvs->kv_rw);
    return ret;
#endif

    return NULL;
};

// 리스트 사용
struct KVS_NODE_T* kv_get_range(struct KVS_T* kvs, int start_key, int end_key, int* num_entries) {
    struct LIST_HEAD_T* p_entry;
    struct KVS_NODE_T* p_kvs_node, * p_temp_node, * ret;
    int bk_key, i;

    if (kvs == NULL)
        return NULL;

    pthread_rwlock_rdlock(kvs, &kvs->kv_rw);
    *num_entries = 0;

    ret = (struct KVS_NODE_T*)malloc(sizeof(struct KVS_NODE_T));
    init_list_head(&ret->list);
    

#if(USE==USE_LIST)
    list_for_each(p_entry, &kvs->list) {
        p_kvs_node = list_entry(p_entry, struct KVS_NODE_T, list);

        // 키가 중복된다면 찾았다면
        if (p_kvs_node->key >= start_key && p_kvs_node->key <= end_key) {
            p_temp_node = (struct KVS_NODE_T*)malloc(sizeof(struct KVS_NODE_T));
            p_temp_node->key = p_kvs_node->key;
            p_temp_node->value = p_kvs_node->value;
            list_add(&p_temp_node->list, &ret->list);
            *num_entries += 1;
        }
    }
#elif(USE==USE_HASH)
    for (i = start_key; i <= end_key; i++) {
        bk_key = i / HASH_MOD;
        list_for_each(p_entry, &kvs->bk[bk_key]) {
            p_kvs_node = list_entry(p_entry, struct KVS_NODE_T, list);

            // 키가 중복된다면 찾았다면
            if (p_kvs_node->key >= start_key && p_kvs_node->key <= end_key) {
                p_temp_node = (struct KVS_NODE_T*)malloc(sizeof(struct KVS_NODE_T));
                p_temp_node->key = p_kvs_node->key;
                p_temp_node->value = p_kvs_node->value;
                list_add(&p_temp_node->list, &ret->list);
                *num_entries += 1;
            }
        }
    }
#elif(USE==USE_SKIP)
    ret = skiplist_getrange(kvs, start_key, end_key,num_entries, ret);
#endif
    pthread_rwlock_unlock(kvs, &kvs->kv_rw);
    return ret;

};



int kv_delete(struct KVS_T* kvs, int key) {
    int found = 0;
    struct LIST_HEAD_T* p_entry, * tmp;
    struct KVS_NODE_T* p_kvs_node;
    int bk_key;

    if (kvs == NULL)
        return -1;

    pthread_rwlock_wrlock(&kvs->kv_rw);


#if(USE==USE_LIST)
    list_for_each_safe(p_entry, tmp, &kvs->list) {
        p_kvs_node = list_entry(p_entry, struct KVS_NODE_T, list);

        // 찾으면 삭제
        if (p_kvs_node->key == key) {
            found = 1;
            list_del(&p_kvs_node->list);	// 삭제
            free(p_kvs_node);		// 메모리 해제
        }
    }
#elif(USE==USE_HASH)
    bk_key = key % HASH_MOD;
    list_for_each_safe(p_entry, tmp, &kvs->bk[bk_key]) {
        p_kvs_node = list_entry(p_entry, struct KVS_NODE_T, list);

        // 찾으면 삭제
        if (p_kvs_node->key == key) {
            found = 1;
            list_del(&p_kvs_node->list);	// 삭제
            free(p_kvs_node);		// 메모리 해제
        }
    }
#elif(USE==USE_SKIP)
    found = skiplist_delete(kvs, key);
#endif


    pthread_rwlock_unlock(&kvs->kv_rw);
    //찾아서 삭제했을 경우 1 반환
    if (found) { return 1; }
    else { return 0; }
}