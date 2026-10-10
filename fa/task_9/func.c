#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "../utils.h"

#define arr_size 100

status_code parse_args(int argc, char *argv[], long *a, long *b){
    if (argc != 3)
        return ERR_WRONG_ARG_COUNT;

    char *endptr1, *endptr2;
    *a = strtol(argv[1], &endptr1, 10);
    *b = strtol(argv[2], &endptr2, 10);

    if (*a == LONG_MAX || *a == LONG_MIN ||
        *b == LONG_MAX || *b == LONG_MIN)
        return ERR_INVALID_NUMBER;

    if (*endptr1 != '\0' || endptr1 == argv[1] || 
        *endptr2 != '\0' || endptr2 == argv[2])
        return ERR_INVALID_NUMBER;

    if (*a > *b) return ERR_RANGE_MISMATCH;

    return SUCCESS;
}

void swap_min_max(long* arr){
    int min_idx = 0, max_idx = 0;

    for (int i = 1; i < arr_size; ++i){
        if (arr[i] < arr[min_idx])
            min_idx = i;
        
        if (arr[i] > arr[max_idx])
            max_idx = i;
    }

    long temp = arr[min_idx];
    arr[min_idx] = arr[max_idx];
    arr[max_idx] = temp;
}

void print_arr(const long* arr, const int size){
    if (arr != NULL)
        printf("%ld", arr[0]);

    for (int i = 1; i < size; ++i){
        printf(" %ld", arr[i]);
    }
    printf("\n");
}

void fill_arr(long *arr, const int size, const long a, const long b){
    for (int i = 0; i < size; ++i)
        arr[i] = a + rand() % (b - a + 1);
}

long find_closest_elem(const long a, const long *arr_B, const int size_B){
    if (a <= arr_B[0]) return arr_B[0];
    if (a >= arr_B[size_B - 1]) return arr_B[size_B - 1];

    int l = 0, r = size_B - 1;
    long closest = arr_B[0];
    long min_diff = labs(closest - a);

    while (l <= r){
        int mid = (r - l) / 2 + l;
        long diff = labs(arr_B[mid] - a);

        if (diff < min_diff){
            min_diff = diff;
            closest = arr_B[mid];
        }

        if (arr_B[mid] > a)
            r = mid - 1;
        else if (arr_B[mid] < a)
            l = mid + 1;
        else
            return arr_B[mid];
    }

    return closest;
}

void fill_arr_C(long *arr_C, const long *arr_A, const long *arr_B, const int size_AC, const int size_B){
    for (int i = 0; i < size_AC; ++i){
        arr_C[i] = arr_A[i];
        arr_C[i] += find_closest_elem(arr_A[i], arr_B, size_B);
    }
}

int compare_longs(const void *a, const void *b){
    long arg1 = *(const long *)a;
    long arg2 = *(const long *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}
