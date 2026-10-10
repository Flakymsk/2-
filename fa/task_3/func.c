#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include "../utils.h"

status_code parse_flag(int argc, char* argv[], char* flag){
    if (argc < 2)
        return ERR_WRONG_ARG_COUNT;

    if (strlen(argv[1]) != 2 || (argv[1][0] != '-' && argv[1][0] != '/'))
        return ERR_WRONG_FLAG;

    *flag = argv[1][1];
    return SUCCESS;
}

status_code parse_args(int argc, char *argv[], const char flag, double *arr_d, long *arr_l){
    char *endptr;

    if (flag == 'q' || flag == 't'){
        if (argc != 6)
            return ERR_WRONG_ARG_COUNT;

        for (int i = 0; i < 4; ++i){
            arr_d[i] = strtod(argv[i + 2], &endptr);

            if (arr_d[i] == HUGE_VAL || *endptr != '\0' || endptr == argv[i + 2])
                return ERR_INVALID_NUMBER;
            
            if (i == 0 && arr_d[i] <= 0.0)
                return ERR_INVALID_NUMBER;

            if (flag == 't' && i > 0 && arr_d[i] <= 0.0)
                return ERR_INVALID_NUMBER;
        }
    } else {
        if (argc != 4)
            return ERR_WRONG_ARG_COUNT;
        
        for (int i = 0; i < 2; ++i){
            arr_l[i] = strtol(argv[i + 2], &endptr, 10);

            if (*endptr != '\0' || endptr == argv[i + 2] ||
                arr_l[i] == 0 || arr_l[i] == LONG_MAX || arr_l[i] == LONG_MIN)
                return ERR_INVALID_NUMBER;
        }
    }

    return SUCCESS;
}

void swap(double *a, double *b){
    double temp = *a;
    *a = *b;
    *b = temp;
}

void print_bool(const bool x){
    printf("%s\n", (x == true ? "true" : "false"));
}

void solve_quad_equation(const double a, const double b, const double c, const double eps){
    if (fabs(a) < eps){
        if (fabs(b) < eps){
            if (fabs(c) < eps) 
                printf("a = %f, b = %f, c = %f, inf solutions\n", a, b, c);
            else 
                printf("a = %f, b = %f, c = %f, zero solutions\n", a, b, c); 
        } else {
            printf("a = %f, b = %f, c = %f, x = %f\n", a, b, c, -c / b);
        }
        return;
    }

    double disc = b * b - 4 * a * c;

    if (disc > eps){
        printf("a = %f, b = %f, c = %f, x1 = %f, x2 = %f\n", a, b, c, (-b - sqrt(disc)) / (2.0 * a), (-b + sqrt(disc)) / (2.0 * a));
    } else if (disc < -eps){
        double re = -b / (2.0 * a);
        double im = sqrt(fabs(disc)) / (2.0 * a);
        printf("a = %f, b = %f, c = %f, x1 = %f - %fi, x2 = %f + %fi\n", a, b, c, re, im, re, im);
    } else {
        printf("a = %f, b = %f, c = %f, x = %f\n", a, b, c, -b / (2.0 * a));
    }
}

bool is_unique_permutation(double history[][3], int count, double a, double b, double c, double eps) {
    for (int i = 0; i < count; ++i) {
        if (fabs(history[i][0] - a) < eps && fabs(history[i][1] - b) < eps && fabs(history[i][2] - c) < eps)
            return false;
    }
    return true;
}

void solve_all_permutations(double eps, double coef1, double coef2, double coef3) {
    double base_coeffs[3] = {coef1, coef2, coef3};
    double history[6][3];
    int unique_count = 0;

    int p[6][3] = {
        {0, 1, 2}, {0, 2, 1}, {1, 0, 2},
        {1, 2, 0}, {2, 0, 1}, {2, 1, 0}
    };

    for (int i = 0; i < 6; ++i) {
        double a = base_coeffs[p[i][0]];
        double b = base_coeffs[p[i][1]];
        double c = base_coeffs[p[i][2]];

        if (is_unique_permutation(history, unique_count, a, b, c, eps)) {
            history[unique_count][0] = a;
            history[unique_count][1] = b;
            history[unique_count][2] = c;
            unique_count++;
            solve_quad_equation(a, b, c, eps);
        }
    }
}

bool check_triangle_sides(const double eps, double a, double b, double c){
    if (a > b) swap(&a, &b);
    if (b > c) swap(&b, &c);

    if (fabs(c * c - a * a - b * b) < eps)
        return true;
    else
        return false;
}
