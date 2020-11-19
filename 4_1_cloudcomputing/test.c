#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "list.h"
#include "kvs.h"
#include "skiplist.h"

#include "STRUCT.h"	//노드수, 스레드수, 스레드 관련 구조체

// 해쉬테이블 추가후 실험
#include "method.h"


int singleTest(); // 리스트, 해쉬,스킵 사용 kvs 함수 작동 확인
int main1();// 해쉬테이블 추가후 실험

int main() {

    //singleTest();
    main1();

    printf("\nend\n");
    return 0;
}

int singleTest() {
    // 동작테스트
    struct KVS_T* my_kvs;
    int i, num=0;
    struct KVS_NODE_T* temp;
    // 1. create key/value store
    my_kvs = kv_create_db();	// 생성 테스트
    if (my_kvs == NULL) {
        printf("kv create if failed\n");
        getchar();
        return -1;
    }
    for (i = 0; i < 100; i++) {	// 삽입 테스트
        struct KVS_NODE_T temp;
        temp.key = i;
        temp.value = i;
        kv_put(my_kvs, &temp);
    }
    kv_delete(my_kvs,5);	// 삭제 테스트
    kv_delete(my_kvs, 9);

    temp = kv_get_range(my_kvs, 5,9, &num);	// 범위 테스트
    printf("%d\n", num);

    temp = kv_get(my_kvs, 15);	// get 테스트
    printf("%d\n", temp->value);
    temp = kv_get(my_kvs, 5);
    //printf("%d\n", temp->value);

    kv_destroy_db(my_kvs);	// 삭제테스트
    //kv_get(my_kvs, 5);

    return 0;

    // SKIP 잘동작
    // 해쉬 잘동작
}


int main1() {
    struct KVS_T* my_kvs;
    int i;
    // 1. create key/value store
    my_kvs = kv_create_db();
    if (my_kvs == NULL) {
        printf("kv create if failed\n");
        getchar();

        return -1;
    }


    // 사전에 key-value store에 필요한 key 개수만큼 채워라!
    for (i = 0; i < NUM_NODES; i++) {
        struct KVS_NODE_T temp;
        temp.key = i;
        temp.value = i;
        kv_put(my_kvs, &temp);//////////////
    }

    
    printf("start sequential write and read\n");
    do_benchmark(my_kvs, NUM_THREADS, NULL);////////////////////////////////////////////////////////
    printf("finish\n");
    

    kv_destroy_db(my_kvs);

    printf("test is done!\n");

    return 0;
}
