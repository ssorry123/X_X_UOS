#pragma once


#define RATIO 9 // 쓰기 스레드 수


void search(void* arg) {
    int i;
    struct THREAD_STATE_T* ts = (struct THREAD_STATE_T*)arg;
    struct KVS_NODE_T* p_node;


    for (i = 0; i < NUM_NODES; i++) {

        p_node = kv_get(ts->kvs, i);

        if (p_node) {
            //printf("s%2d ",p_node->key);
            ts->done++;
        }
        if ((ts->done % 10000) == 0)
            printf(".");
    }
}

void insert(void* arg) {
    int i, ret;
    struct THREAD_STATE_T* ts = (struct THREAD_STATE_T*) arg;
    struct KVS_NODE_T node;

    for (i = 0; i < NUM_NODES; i++) {



        node.key = i;
        node.value = i;
        ret = kv_put(ts->kvs, &node);
        //printf("i%2d ",i);
        ts->done++;



        if ((ts->done % 10000) == 0)
            printf(".");
    }
}
// 쓰레드 메인 함수
void* thread_main(void* arg) {
    struct THREAD_ARG_T* thread_arg = arg;
    struct SHARED_STATE_T* ss = thread_arg->ss;
    struct THREAD_STATE_T* ts = thread_arg->ts;

    //-
    pthread_mutex_lock(&ss->mu);

    ss->num_inited++;	// 자신의 쓰레드가 초기화됬다고 알린다.

    // 전체 쓰레드가 다 만들어지면 전부 깨운다
    // dobenchmark에 있는 것을 깨우는듯
    if (ss->num_inited >= ss->total) {
        pthread_cond_broadcast(&ss->cv);
    }
    // start가 0이면 계속 기다린다
    // 동시시작을 위해서
    // 마지막에 초기화되는 쓰레드를 제외하고 여기서 잠들다..
    // start가 1이되면 while을 탈출하고 
    while (!ss->start) {
        // 내부적으로 mu반환, 신호가 오면 mu 획득
        pthread_cond_wait(&ss->cv, &ss->mu);
    }
    // 획득한 mu 반환
    pthread_mutex_unlock(&ss->mu);
    //-

    // 스레드 시작전 시간 기록
    ts->start = time(NULL);

    // 실제 스레드 시작
    (thread_arg->tf)((void*)ts);


    // 종료
    ts->finish = time(NULL);

    // 다시 락을 건다.
    pthread_mutex_lock(&ss->mu);
    ss->num_done++;	// 종료 카운트 증가
    if (ss->num_done >= ss->total) {
        pthread_cond_broadcast(&ss->cv);
    }
    pthread_mutex_unlock(&ss->mu);

    return NULL;
}

// kvs, 실행시킬 스레드의 개수, 함수 이름
void do_benchmark(struct KVS_T* kvs, int num_threads, THREAD_FUNC tf) {
    int i, j, ret;
    double elapsed = 0, num_ops = 0;
    struct SHARED_STATE_T shared;	//여러 스레드가 공유
    struct THREAD_STATE_T* tss;		//스레드마다 존재
    struct THREAD_ARG_T* args;		//스레드마다 존재

    // 공유 state 초기화
    pthread_mutex_init(&shared.mu, NULL);
    pthread_cond_init(&shared.cv, NULL);
    shared.num_inited = 0;
    shared.num_done = 0;
    shared.start = 0;	// 시작안했을땐 0
    shared.total = num_threads;

    // 메모리 할당후 모두 NULL로 할당
    args = (struct THREAD_ARG_T*)malloc(sizeof(struct THREAD_ARG_T) * num_threads);
    if (args == NULL) {
        printf("args malloc failed\n");
        return;
    }
    memset((void*)args, 0x00, sizeof(struct THREAD_ARG_T) * num_threads);

    tss = (struct THREAD_STATE_T*) malloc(sizeof(struct THREAD_STATE_T) * num_threads);
    if (tss == NULL) {
        printf("tss malloc failed\n");
        free(args);
        return;
    }
    memset((void*)tss, 0x00, sizeof(struct THREAD_STATE_T) * num_threads);

    // 스레드에 전달하는 args 초기화

    //j = num_threads / RATIO_1;
    //printf("\n\nj = %d\n\n", j);

    // 쓰기 먼저
    for (i = 0; i < RATIO; i++) {
        args[i].ss = &shared;	// 공유구조체
        args[i].ts = &tss[i];	// 각각의 쓰레드 구조체
        args[i].ts->kvs = kvs;	// kvs
        args[i].tf = insert;		// 실행할 함수//////////////////////////////////////////////////////////////////////////////////////////////////////////

        // 쓰레드 생성
        pthread_create(&args[i].ts->tid, NULL, thread_main, &args[i]);/////////////////////////////////////////////////////////////////////////
    }
    for (i = RATIO; i < NUM_THREADS; i++) {
        args[i].ss = &shared;	// 공유구조체
        args[i].ts = &tss[i];	// 각각의 쓰레드 구조체
        args[i].ts->kvs = kvs;	// kvs
        args[i].tf = search;		// 실행할 함수////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // 쓰레드 생성
        pthread_create(&args[i].ts->tid, NULL, thread_main, &args[i]);///////////////////////////////////////////////////////////////////////////
    }



    // 락을 건 후
    // 스레드가 전부 준비가 되면
    pthread_mutex_lock(&shared.mu);
    while (shared.num_inited < num_threads) {
        //내부적으로 mu 반환, 신호가 오면 mu 획득
        pthread_cond_wait(&shared.cv, &shared.mu);
    }

    // 1로 놓고 전부 깨운다.
    shared.start = 1;
    pthread_cond_broadcast(&shared.cv);
    while (shared.num_done < num_threads) {
        pthread_cond_wait(&shared.cv, &shared.mu);
    }
    pthread_mutex_unlock(&shared.mu);

    // 다 끝날떄까지 기다림
    for (i = 0; i < num_threads; i++) {
        ret = pthread_join(args[i].ts->tid, NULL);
    }

    // results
    for (i = 0; i < num_threads; i++) {
        elapsed = difftime(tss[i].finish, tss[i].start);
        num_ops += tss[i].done;
    }

    printf("\nops = %f\n", num_ops / elapsed);

    // free
    free(tss);
    free(args);
}