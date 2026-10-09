#include <stdlib.h>
#include <limits.h>
#include "../utils.h"

status_code parse_base(const int argc, const char *argv[], long *base){
    if (argc < 3)
        return ERR_WRONG_ARG_COUNT;

    char *endptr;
    *base = strtol(argv[1], &endptr, 10);

    if (*base < 2 || *base > 36)
        return ERR_INVALID_NUMBER;

    if (*endptr != '\0' || endptr == argv[1])
        return ERR_INVALID_NUMBER;
    
    return SUCCESS;
}

status_code parse_number(const char *arg, long *number, const long base){

    char *endptr;
    *number = strtol(*arg, endptr, base);

    if (*number == LONG_MAX || *number == LONG_MIN)
        return ERR_INVALID_NUMBER;

    if (*endptr != '\0' || endptr == *arg)
        return ERR_INVALID_NUMBER;
    
    return SUCCESS;
}

void print_number_base_n(long number, int n){
    if (number < 0) {
        printf("-");
        number = -number;
    }

    if (number >= n) {
        print_num_base_n(number / n, n);
    }

    int digit = number % n;
    if (digit < 10) {
        printf("%d", digit);
    } else {
        printf("%c", 'A' + (digit - 10));
    }
}


void proceed_number(const long number, long *max_val, long *sum){
    if (abs(number) > abs(*max_val))
        *max_val = number;
    
    *sum += number;
}