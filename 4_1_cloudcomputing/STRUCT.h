#pragma once


#define NUM_NODES		1000000
#define NUM_THREADS		10


// void *search(void *arg) {}
// void *insert(void *arg) {}
// void *delete(void *arg) {}
typedef void (*THREAD_FUNC)(void*);

// 공유 구조체
struct SHARED_STATE_T {
    pthread_mutex_t mu;
    pthread_cond_t	cv;
    int total;		// 전체 쓰레드 게수
    int num_inited;	// 초기화한 쓰레드 개수
    int num_done;	// 끝난 쓰레드 개수
    int start;		// 쓰레드가 시작했나?
};

// 각각의 쓰레드가 가지는 구조체
struct THREAD_STATE_T {
    pthread_t tid;
    int rand_seed;	 /*1: 1-1000000, 2: 1000001-2000000*/
    time_t start;
    time_t finish;
    int done;	// 작업을 몇개나 수행하였나
    struct KVS_T* kvs;
};


// 쓰레드에 전달할 arg
struct THREAD_ARG_T {
    struct SHARED_STATE_T* ss;	// 공유 state
    struct THREAD_STATE_T* ts;	// 스레드 state
    THREAD_FUNC tf;				// 스레드에서 실행할 함수
};