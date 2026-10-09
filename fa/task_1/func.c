#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "utils.h"

status_code parse_args(int argc, char *argv[], long *num, char *c){
    if (argc != 3)
        return ERR_WRONG_ARG_COUNT;

    char *endptr1;
    *num = strtol(argv[1], &endptr1, 10);
    
    if (strlen(argv[2]) != 2)
        return ERR_WRONG_FLAG;

    *c = argv[2][1];

    if (*num == LONG_MAX || *num == LONG_MIN)
        return ERR_INVALID_NUMBER;

    if (*endptr1 != '\0' || endptr1 == argv[1])
        return ERR_INVALID_NUMBER;

    return SUCCESS;
}

void print_bool(const bool x){
    printf("%s\n", (x == true ? "true" : "false"));
}

void print_x(const long x){
    printf("%ld\n", x);
}

void print_str(const char *str){
    printf("%s\n", str);
}

void print_arr(const long *arr, const int amount){
    if (!amount){
        printf("empty arr\n");
        return;
    }

    printf("%ld", arr[0]);
    for (int i = 2; i < amount; ++i)
        printf(" %ld", arr[i]);
    printf("\n");
}

long* get_natural_numbers_multiples_x(const long x, int *amount){
    static long result[100];

    int idx = 0;
    for (long i = 2 * x; i <= 100; i += x)
        result[idx++] = i;

    *amount = idx;
    return result;
}

bool is_prime_number(const long x){
    if (x < 2) return false; 

    for (long i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return false;
    
    return true;
}

char* count_num_hex(unsigned long x){
    static char num_hex_str[17];
    const char hex_digits[] = "0123456789ABCDEF";
    int idx = 16;
    num_hex_str[idx] = '\0';
    
    do{
        num_hex_str[--idx] = hex_digits[x % 16];
        x /= 16;
    } while (x > 0);

    return &num_hex_str[idx];
}

void print_table_pows(const long x){
    for (long i = 1; i <= 10; ++i){
        long num = i;

        for (long j = 1; j <= x; ++j){
            printf("%ld ", num);
            num *= i;
        }

        printf("\n");
    }
}

long sum_from_1_to_x(const long x){
    long sum = 0;
    
    for (int i = 1; i <= x; ++i)
        sum += i;
    
    return sum;
}

long fact_x(const long x){
    long fact = 1;

    for (long i = 2; i <= x; ++i)
        fact *= i;
    
    return fact;
}