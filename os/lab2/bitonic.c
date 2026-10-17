#include <stddef.h>

void bitonic_sort_serial(int *arr, size_t arr_size) {
    int log_n = 0;
    while ((1 << log_n) < arr_size) log_n++;

    for (int step_p = 0; step_p < log_n; step_p++) {
        for (int step_q = 0; step_q <= step_p; step_q++) {
            int distance = 1 << (step_p - step_q);
            for (size_t i = 0; i < arr_size; i++) {
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
        }
    }
}
