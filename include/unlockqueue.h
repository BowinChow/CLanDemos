//
// Created by Bowin on 2023/4/2.
//

#ifndef CLANDEMO_UNLOCKQUEUE_H
#define CLANDEMO_UNLOCKQUEUE_H


#include <pthread.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>
#include <time.h>


typedef int lfr_ele_t;
typedef struct lfr_queue_t {
    size_t head;
    size_t tail;
    lfr_ele_t *ele;
    size_t size;
    pthread_mutex_t lock;
}
        lfr_queue;

typedef bool (*push_fn)(lfr_queue *queue, const lfr_ele_t *ele);

typedef bool (*pop_fn)(lfr_queue *queue, lfr_ele_t *ele);

typedef struct thread_arg_t {
    lfr_queue *queue;
    char type;
    push_fn push;
    pop_fn pop;
} thread_arg;

void lfr_queue_init(lfr_queue *queue, size_t size);

void lfr_free(lfr_queue *queue);

size_t lfr_next_index(lfr_queue *queue, size_t index);

bool lfr_lock_push(lfr_queue *queue, const lfr_ele_t *ele);

bool lfr_lock_pop(lfr_queue *queue, lfr_ele_t *ele);

bool lfr_unlock_push(lfr_queue *queue, const lfr_ele_t *ele);

bool lfr_unlock_pop(lfr_queue *queue, lfr_ele_t *ele);

double time_diff(struct timespec *start, struct timespec *end);

void *thread_func(void *a);

void init_demo();


#endif //CLANDEMO_UNLOCKQUEUE_H



