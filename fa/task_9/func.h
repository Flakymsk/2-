#ifndef func_9
#define func_9

#include "../utils.h"

status_code parse_args(int argc, char *argv[], long *a, long *b);
void swap_min_max(long* arr);
void print_arr(const long* arr, const int size);
void fill_arr(long *arr, const int size, const long a, const long b);
void fill_arr_C(long *arr_C, const long *arr_A, const long *arr_B, const int size_AC, const int size_B);
int compare_longs(const void *a, const void *b);

#endif
