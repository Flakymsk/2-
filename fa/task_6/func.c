#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>
#include "../utils.h"

status_code parse_flag(int argc, char* argv[], char *flag){
    if (argc < 2)
        return ERR_WRONG_ARG_COUNT;

    if (strlen(argv[1]) != 2 || argv[1][1] < '1' || argv[1][1] > '6')
        return ERR_WRONG_FLAG;
    
    *flag = argv[1][1];

    return SUCCESS;
}

status_code parse_task1(int argc, char *argv[], double coords[8]){
    if (argc != 10)
        return ERR_WRONG_ARG_COUNT;

    char *endptr;

    for (int i = 0; i < 8; ++i) {
        coords[i] = strtod(argv[2 + i], &endptr);
        if (*endptr != '\0' || endptr == argv[2 + i] || coords[i] == HUGE_VAL || coords[i] == -HUGE_VAL)
            return ERR_INVALID_NUMBER;
    }

    return SUCCESS;
}

status_code parse_task2(int argc, char *argv[], double *x, double coeffs[4]){
    if (argc != 7)
        return ERR_WRONG_ARG_COUNT;

    char *endptr;

    *x = strtod(argv[2], &endptr);
    if (*endptr != '\0' || endptr == argv[2] || *x == HUGE_VAL || *x == -HUGE_VAL)
        return ERR_INVALID_NUMBER;

    for (int i = 0; i < 4; ++i) {
        coeffs[i] = strtod(argv[3 + i], &endptr);
        if (*endptr != '\0' || endptr == argv[3 + i] || coeffs[i] == HUGE_VAL || coeffs[i] == -HUGE_VAL)
            return ERR_INVALID_NUMBER;
    }

    return SUCCESS;
}

status_code parse_task3(int argc, char *argv[], long *base, const char *strings[3]){
    if (argc != 5)
        return ERR_WRONG_ARG_COUNT;

    char *endptr;

    *base = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || endptr == argv[2] || *base < 2 || *base > 36)
        return ERR_INVALID_NUMBER;

    strings[0] = argv[3];
    strings[1] = argv[4];
    strings[2] = argv[5];

    return SUCCESS;
}

status_code parse_task4(int argc, char *argv[], double nums[3]){
    if (argc != 5)
        return ERR_WRONG_ARG_COUNT;

    char *endptr;

    for (int i = 0; i < 3; ++i) {
        nums[i] = strtod(argv[2 + i], &endptr);
        if (*endptr != '\0' || endptr == argv[2 + i] || nums[i] == HUGE_VAL || nums[i] == -HUGE_VAL)
            return ERR_INVALID_NUMBER;
    }

    return SUCCESS;
}

status_code parse_task5(int argc, char *argv[], double *x, long *pow_val){
    if (argc != 4)
        return ERR_WRONG_ARG_COUNT;

    char *endptr;

    *x = strtod(argv[2], &endptr);
    if (*endptr != '\0' || endptr == argv[2] ||
        *x == HUGE_VAL || *x == -HUGE_VAL)
        return ERR_INVALID_NUMBER;

    *pow_val = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || endptr == argv[3] || 
        *pow_val == LONG_MAX || *pow_val == LONG_MIN)
        return ERR_INVALID_NUMBER;

    return SUCCESS;
}

status_code parse_task6(int argc, char *argv[], double *a, double *b, double *eps){
    if (argc != 5)
        return ERR_WRONG_ARG_COUNT;

    char *endptr;

    *a = strtod(argv[2], &endptr);
    if (*endptr != '\0' || endptr == argv[2] || 
        *a == HUGE_VAL || *a == -HUGE_VAL)
        return ERR_INVALID_NUMBER;

    *b = strtod(argv[3], &endptr);
    if (*endptr != '\0' || endptr == argv[3] || 
        *b == HUGE_VAL || *b == -HUGE_VAL)
        return ERR_INVALID_NUMBER;

    *eps = strtod(argv[4], &endptr);
    if (*endptr != '\0' || endptr == argv[4] || 
        *eps == HUGE_VAL || *eps <= 0.0)
        return ERR_INVALID_NUMBER;

    if (*a > *b)
        return ERR_RANGE_MISMATCH;

    return SUCCESS;
}


bool is_figure_convex(const long amount, ...){
    if (amount < 3)
        return true;

    va_list args;
    va_start(args, amount);

    double first_x = va_arg(args, double);
    double first_y = va_arg(args, double);
    double second_x = va_arg(args, double);
    double second_y = va_arg(args, double);

    double prev_x1 = first_x;
    double prev_y1 = first_y;
    double prev_x2 = second_x;
    double prev_y2 = second_y;

    bool negative = false;
    bool positive = false;

    for (long i = 2; i < amount; ++i){
        double curr_x = va_arg(args, double);
        double curr_y = va_arg(args, double);

        double dx1 = prev_x2 - prev_x1;
        double dy1 = prev_y2 - prev_y1;
        double dx2 = curr_x - prev_x2;
        double dy2 = curr_y - prev_y2;

        double cross_product = dx1 * dy2 - dy1 * dx2;

        if (cross_product < 0.0) negative = true;
        if (cross_product > 0.0) positive = true;
        if (negative && positive){
            va_end(args);
            return false;
        }

        prev_x1 = prev_x2;
        prev_y1 = prev_y2;
        prev_x2 = curr_x;
        prev_y2 = curr_y;
    }
    va_end(args);

    double dx1 = prev_x2 - prev_x1;
    double dy1 = prev_y2 - prev_y1;
    double dx2 = first_x - prev_x2;
    double dy2 = first_y - prev_y2;
    double last1 = dx1 * dy2 - dy1 * dx2;

    if (last1 < 0.0) negative = true;
    if (last1 > 0.0) positive = true;
    if (negative && positive)
        return false;

    dx1 = first_x - prev_x2;
    dy1 = first_y - prev_y2;
    dx2 = second_x - first_x;
    dy2 = second_y - first_y;
    double last2 = dx1 * dy2 - dy1 * dx2;

    if (last2 < 0.0) negative = true;
    if (last2 > 0.0) positive = true;
    if (negative && positive) 
        return false;

    return true;
}


double count_polynomial(const double x, const long pow, ...){
    va_list args;
    va_start(args, pow);

    double result = va_arg(args, double);

    for (int i = 0; i < pow; ++i)
        result = result * x + va_arg(args, double);

    va_end(args);

    return result;
}

bool is_kaprekar(const long num, const long base) {
    if (num == 0) {
        return true;
    }

    long square = num * num;
    long divisor = 1;

    while (divisor <= square) {
        divisor *= base;

        long left = square / divisor;
        long right = square % divisor;

        
        if (right > 0 && left + right == num)
            return true;
        
    }

    return false;
}

status_code find_kaprekar_nums(char* str_ans[], const long base, const long amount, ...){
    va_list args;
    va_start(args, amount);

    long iter = 0;

    for (long i = 0; i < amount; ++i){
        char *str = va_arg(args, char*);
        char* endptr;

        long num = strtol(str, &endptr, base);

        if (num == LONG_MAX || num == LONG_MIN ||
            *endptr != '\0' || endptr == str)
            return ERR_INVALID_NUMBER;

        if (is_kaprekar(num, base))
            str_ans[iter++] = str;
        
    }

    str_ans[iter] = NULL;
    va_end(args);

    return SUCCESS;
}

double geometric(const long amount, ...){
    va_list args;
    va_start(args, amount);

    double mul = 1.0;

    for (int i = 0; i < amount; ++i)
        mul *= va_arg(args, double);

    va_end(args);

    return pow(mul, 1.0 / amount);
}

double fast_pow(const double x, const long pow){
    if (pow == 0.0)
        return 1.0;
    
    if (pow < 0){
        if (x == 0.0)
            return 0.0;
        
        return 1.0 / fast_pow(x, -pow);
    }

    if (pow % 2 == 0){
        double half = fast_pow(x, pow / 2);

        return half * half;
    }

    else{
        return x * fast_pow(x, pow - 1);
    }
}

double equation_1(double x){
    return 4 * x - 1;
}

double equation_2(double x){
    return x * x * x;
}

double solve_dichotomy(double a, double b, const double eps, double (*func)(double)){
    if ((*func)(a) * (*func)(b) >= 0)
        return NAN;

    while (b - a > eps){
        double x_mid = (b - a) / 2 + a;
        double y_mid = (*func)(x_mid);

        if ((*func)(a) * y_mid > 0)
            a = x_mid;
        else
            b = x_mid;
    }
    
    return (b - a) / 2 + a;
}
