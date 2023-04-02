//
// Created by Bowin on 2023/4/2.
//

#include "unlockqueue.h"
#include <stdlib.h>

void lfr_queue_init(lfr_queue *queue, size_t size) {
    memset(queue, 0, sizeof(*queue));
    queue->size = size + 1;
    queue->ele = (lfr_ele_t *) malloc(sizeof(lfr_ele_t) * queue->size);
    pthread_mutex_init(&queue->lock, 0);
}

void lfr_free(lfr_queue *queue) {
    free(queue->ele);
}

size_t lfr_next_index(lfr_queue *queue, size_t index) {
    return (index + 1) % queue->size;
}

bool lfr_lock_push(lfr_queue *queue, const lfr_ele_t *ele) {
    pthread_mutex_lock(&queue->lock);
    bool success = false;
    size_t ntail = lfr_next_index(queue, queue->tail);
    if (ntail != queue->head) {
        queue->ele[queue->tail] = *ele;
        queue->tail = ntail;
        success = true;
    }

    pthread_mutex_unlock(&queue->lock);
    return success;

}

bool lfr_lock_pop(lfr_queue *queue, lfr_ele_t *ele) {
    pthread_mutex_lock(&queue->lock);
    bool success = false;
    if (queue->head != queue->tail) {
        *ele = queue->ele[queue->head];
        queue->head = lfr_next_index(queue, queue->head);
        success = true;
    }

    pthread_mutex_unlock(&queue->lock);
    return success;
}

bool lfr_unlock_push(lfr_queue *queue, const lfr_ele_t *ele) {
    size_t ctail = atomic_load(&queue->tail);
    size_t ntail = lfr_next_index(queue, ctail);
    if (ntail != atomic_load(&queue->head)) {
        queue->ele[ctail] = *ele;
        atomic_store(&queue->tail, ntail);
        return true;
    }

    return false;

}

bool lfr_unlock_pop(lfr_queue *queue, lfr_ele_t *ele) {
    size_t chead = atomic_load(&queue->head);
    if (chead != atomic_load(&queue->tail)) {
        *ele = queue->ele[chead];
        atomic_store(&queue->head, lfr_next_index(queue, chead));
        return true;
    }

    return false;
}

double time_diff(struct timespec *start, struct timespec *end) {
    long sec = end->tv_sec - start->tv_sec;
    long nsec = end->tv_nsec - start->tv_nsec;
    return sec * 1000.0 + nsec * 1000000.0;
}

void *thread_func(void *a) {
    thread_arg *arg = (thread_arg *) a;
    lfr_queue *queue = arg->queue;
    struct timespec time1, time2;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1);
    if (arg->type == 'W') {

        lfr_ele_t e = 10000000;
        while (true) {
            if (arg->push(queue, &e)) {
                if (--e < 0) {
                    break;
                }
            }
        }
    } else {
        lfr_ele_t e;
        while (true) {
            if (arg->pop(queue, &e)) {
                if (e == 0) {
                    break;
                }
            }
        }
    }

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time2);
    printf("%c Thread time = %fms\n", arg->type, time_diff(&time1, &time2));
    return NULL;
}

void init_demo() {
    struct test_case {
        push_fn push;
        pop_fn pop;
        const char *desc;
    }
            cases[] = {
            {lfr_lock_push,   lfr_lock_pop,   "mutex_lock"},
            {lfr_unlock_push, lfr_unlock_pop, "atomic operation"},
    };


    for (int k = 0; k < sizeof(cases) / sizeof(cases[0]); ++k) {

        printf("----------------------------------------\n");
        printf("%s\n", cases[k].desc);
        lfr_queue queue;
        lfr_queue_init(&queue, 100);
        const int NUM = 2;
        pthread_t tid[NUM];
        thread_arg args[NUM];
        int i;
        for (i = 0; i < NUM; ++i) {
            args[i].queue = &queue;
            args[i].type = i == 0 ? 'W' : 'R';
            args[i].push = cases[k].push;
            args[i].pop = cases[k].pop;
            pthread_create(&tid[i], NULL, thread_func, args + i);
        }
        for (i = 0; i < NUM; ++i) {
            pthread_join(tid[i], NULL);

        }
        lfr_free(&queue);

    }
}

