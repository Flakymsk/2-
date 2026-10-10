#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"
#include "../utils.h"

#define arr_size 100

int main(int argc, char *argv[]){
    long a, b;
    status_code msg;

    if ((msg = parse_args(argc, argv, &a, &b)) != SUCCESS){
        print_error_message(msg);
        return 1;
    }

    long arr[arr_size];
    
    srand(time(NULL));

    fill_arr(arr, arr_size, a, b);

    print_arr(arr, arr_size);
    swap_min_max(arr);
    print_arr(arr, arr_size);

    int size_AC = 10 + rand() % (10000 - 10 + 1);
    int size_B = 10 + rand() % (10000 - 10 + 1);

    long *arr_A = (long*)malloc(sizeof(long) * size_AC);
    long *arr_B = (long*)malloc(sizeof(long) * size_B);
    long *arr_C = (long*)malloc(sizeof(long) * size_AC);

    if (arr_A == NULL || arr_B == NULL || arr_C == NULL){
        print_error_message(ERR_MEMORY_ALLOC);
        if (arr_A) free(arr_A);
        if (arr_B) free(arr_B);
        if (arr_C) free(arr_C);
        return 1;
    }

    fill_arr(arr_A, size_AC, -1000, 1000);
    fill_arr(arr_B, size_B, -1000, 1000);
    qsort(arr_B, size_B, sizeof(long), compare_longs);

    fill_arr_C(arr_C, arr_A, arr_B, size_AC, size_B);

    //print_arr(arr_A, size_AC);
    //print_arr(arr_B, size_B);
    //print_arr(arr_C, size_AC);

    free(arr_A);
    free(arr_B);
    free(arr_C);
    
    return 0;
}
