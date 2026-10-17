#include <stddef.h>
#include <pthread.h>
#include <stdlib.h>

int *p_arr;
size_t p_arr_size;
int p_step_p;
int p_step_q;

typedef struct {
    size_t thread_id;
    size_t n_threads;
} ThreadArgs;

static void *bitonic_worker(void *_args) {
    ThreadArgs *args = (ThreadArgs*)_args;
    int distance = 1 << (p_step_p - p_step_q);
    
    for (size_t i = args->thread_id; i < p_arr_size; i += args->n_threads) {
        if ((i & distance) == 0) {
            int j = i + distance;
            int is_ascending = ((i & (1 << (p_step_p + 1))) == 0);

            if ((p_arr[i] > p_arr[j] && is_ascending) || (p_arr[i] < p_arr[j] && !is_ascending)) {
                int t = p_arr[i]; 
                p_arr[i] = p_arr[j]; 
                p_arr[j] = t;
            }
        }
    }
    return NULL;
}

static void run_parallel_phase(size_t n_threads, pthread_t *threads, ThreadArgs *thread_args) {
    for (size_t i = 0; i < n_threads; ++i) {
        thread_args[i] = (ThreadArgs){
            .thread_id = i,
            .n_threads = n_threads,
        };
        pthread_create(&threads[i], NULL, bitonic_worker, &thread_args[i]);
    }

    for (size_t i = 0; i < n_threads; ++i) {
        pthread_join(threads[i], NULL);
    }
}

void bitonic_sort_parallel(int *arr, size_t arr_size, size_t n_threads, pthread_t *threads, ThreadArgs *thread_args) {
    p_arr = arr;
    p_arr_size = arr_size;

    int log_n = 0;
    while ((1 << log_n) < arr_size) log_n++;

    for (p_step_p = 0; p_step_p < log_n; p_step_p++) {
        for (p_step_q = 0; p_step_q <= p_step_p; p_step_q++) {
            run_parallel_phase(n_threads, threads, thread_args);
        }
    }
}