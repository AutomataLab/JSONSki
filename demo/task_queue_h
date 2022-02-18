#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <pthread.h>

struct TaskQueue {
    // the first record can be processed for current iteration
    long start_idx;
    // the last record can be processed for current iteration
    long end_idx;
    // number of records each thread picks for each iteration
    int batch_size;
    // lock the task-pickup queue
    pthread_mutex_t mutex;
};

static inline int get_batch_size(int num_recs) {
    // according to our evaluations, the following algorithm can reach a good performance.
    int batch_size = 0;
    if (num_recs >= 100000) batch_size = 100;
    else if (num_recs >= 10000) batch_size = 50;
    else if (num_recs >= 1000) batch_size = 15;
    else batch_size = num_recs / 100 + 1;
    return batch_size;
}

static inline bool next_batch(TaskQueue& tq, long& start_idx, long& end_idx) {
    bool is_success = false;
    pthread_mutex_lock(&tq.mutex);
    if (tq.start_idx < tq.end_idx) {
        start_idx = tq.start_idx;
        if (start_idx + tq.batch_size < tq.end_idx) {
            tq.start_idx = start_idx + tq.batch_size;
            end_idx = start_idx + tq.batch_size;
        } else {
            tq.start_idx = tq.end_idx;
            end_idx = start_idx + (tq.end_idx - start_idx);
        }
        is_success = true;
    }
    pthread_mutex_unlock(&tq.mutex);
    return is_success;
}
#endif
