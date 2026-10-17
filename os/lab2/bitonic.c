#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int *arr;
size_t arr_size;
int step_p;
int step_q;

typedef struct {
    size_t thread_id;
    size_t n_threads;
} ThreadArgs;

static void *bitonic_worker(void *_args) {
    ThreadArgs *args = (ThreadArgs*)_args;
    int distance = 1 << (step_p - step_q);
    
    for (size_t i = args->thread_id; i < arr_size; i += args->n_threads) {
        if ((i & distance) == 0) {
            int j = i + distance;
            int is_ascending = ((i & (1 << step_p)) == 0);

            if ((arr[i] > arr[j] && is_ascending) || (arr[i] < arr[j] && !is_ascending)) {
                int t = arr[i]; 
                arr[i] = arr[j]; 
                arr[j] = t;
            }
        }
    }
    return NULL;
}

void run_parallel_phase(size_t n_threads, pthread_t *threads, ThreadArgs *thread_args) {
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

int main(int argc, char **argv) {
    if (argc < 2)
        return 1;
    
    size_t max_threads = atoi(argv[1]);
    if (max_threads < 1) 
        return 1;

    arr_size = 1 << 20; 
    arr = malloc(arr_size * sizeof(int));
    
    for (size_t i = 0; i < arr_size; i++) {
        arr[i] = rand() % 100000;
    }

    pthread_t *threads = malloc(max_threads * sizeof(pthread_t));
    ThreadArgs *thread_args = malloc(max_threads * sizeof(ThreadArgs));

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int log_n = 0;
    while ((1 << log_n) < arr_size) log_n++;

    for (step_p = 0; step_p < log_n; step_p++) {
        for (step_q = 0; step_q <= step_p; step_q++) {
            run_parallel_phase(max_threads, threads, thread_args);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
    printf("Потоков: %4zu -> Время: %f сек.\n", max_threads, time_taken);

    free(thread_args);
    free(threads);
    free(arr);
    return 0;
}
