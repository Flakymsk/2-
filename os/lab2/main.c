#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    size_t thread_id;
    size_t n_threads;
    int *arr;
    size_t arr_size;
    int step_p;
    int step_q;
} ThreadArgs;

void bitonic_sort_serial(int *arr, size_t arr_size);
void bitonic_sort_parallel(int *arr, size_t arr_size, size_t n_threads, pthread_t *threads, ThreadArgs *thread_args);

int *arr;
int *backup_arr;
size_t arr_size;

void reset_array() {
    for (size_t i = 0; i < arr_size; i++) {
        arr[i] = backup_arr[i];
    }
}

double get_time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
}

int main() {
    arr_size = 1 << 20; 
    arr = malloc(arr_size * sizeof(int));
    backup_arr = malloc(arr_size * sizeof(int));
    
    for (size_t i = 0; i < arr_size; i++) {
        backup_arr[i] = rand() % 100000;
    }

    size_t experiments[] = {1, 4, 8, 9, 10, 16, 128, 1024};
    size_t num_experiments = sizeof(experiments) / sizeof(size_t);
    size_t max_threads = 1024; 

    pthread_t *threads = malloc(max_threads * sizeof(pthread_t));
    ThreadArgs *thread_args = malloc(max_threads * sizeof(ThreadArgs));

    struct timespec start, end;

    printf("Битоническая сортировка. Массив: %zu элементов.\n", arr_size);
    printf("=========================================================================\n");
    printf("| Потоки (p) |  Время Tp (сек)  |  Ускорение S  |  Эффективность E (%%)  |\n");
    printf("=========================================================================\n");

    reset_array();
    clock_gettime(CLOCK_MONOTONIC, &start);
    bitonic_sort_serial(arr, arr_size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double t_s = get_time_diff(start, end);
    
    printf("| Последов.  |     %f     |       1.00    |        100.00%%        |\n", t_s);

    for (size_t k = 0; k < num_experiments; k++) {
        size_t p = experiments[k];
        reset_array();
        
        clock_gettime(CLOCK_MONOTONIC, &start);
        bitonic_sort_parallel(arr, arr_size, p, threads, thread_args);
        clock_gettime(CLOCK_MONOTONIC, &end);
        
        double t_p = get_time_diff(start, end);
        double s = t_s / t_p;
        double e = (s / (double)p) * 100.0;
        
        printf("|    %4zu    |     %f     |    %7.2f    |       %7.2f%%        |\n", p, t_p, s, e);

        int sorted = 1;
        size_t index = arr_size;
        for (size_t i = 1; i < arr_size; ++i) {
            if (arr[i] < arr[i - 1]) {
                sorted = 0;
                index = i;
                break;
            }
        }

        if (!sorted) {
            printf("OHHHH MY GOOOOD NO WAYAYAYAYAYAY (%zu)!\n", index);
        }
    }
    printf("=========================================================================\n");

    free(thread_args);
    free(threads);
    free(backup_arr);
    free(arr);
    return 0;
}
