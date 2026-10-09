#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include "../utils.h"

status_code parse_flag(int argc, char* argv[], char* flag){
    if (argc < 2)
        return ERR_WRONG_ARG_COUNT;

    if (strlen(argv[1]) != 2)
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

            if (arr_d[i] == HUGE_VAL || arr_d[i] <= 0.0 ||
                *endptr != '\0' || endptr == argv[i + 2])
                return ERR_INVALID_NUMBER;
            }
    } else{
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

void swap_arr(double *arr, int i, int j){
    double temp = arr[i];
    arr[i] = arr[j];
    arr[j] = arr[i];
}

void solve_quad_equation(const double a, const  double b, const double c, const double eps){
    if (fabs(a) < eps){
        if (fabs(b) < eps)
           if (fabs(c) < eps) printf("a = %f, b = %f, c = %f, inf solutions\n", a, b, c);
           else printf("a = %f, b = %f, c = %f, zero solutions\n", a, b, c); 
        else
            printf("a = %f, b = %f, c = %f, x = %f", a, b, c, -c / b);
        
        return;
    }

    double disc = b * b - 4 * a * c;

    if (disc > eps){
        printf("a = %f, b = %f, c = %f, x1 = %f, x2 = %f", a, b, c, (-b - sqrt(disc)) / (2.0 * a), (-b + sqrt(disc)) / (2.0 * a));
    } else if (disc < eps){
        double re = -b / (2.0 * a);
        double im = sqrt(fabs(disc)) / (2.0 * a);

        printf("a = %f, b = %f, c = %f, x1 = %f - %fi, x2 = %f + %fi", a, b, c, re, im, re, im);
    }
    else
        printf("a = %f, b = %f, c = %f, x = %f", a, b, c, -b / (2.0 * a));
}

void check_quad_coeffs(double *arr, int iter, const double eps){
    if (iter == 3){
        solve_quad_equation(arr[0], arr[1], arr[2], eps);
        return;
    }

    for (int i = iter; i < 3; ++i){
        if (i != iter && fabs(arr[i] - arr[iter]) < eps) continue;

        swap_arr(arr, iter, i);
        check_quad_coeffs(arr, iter + 1, eps);
        swap_arr(arr, iter, i);
    }
}

bool check_triangle_sides (const double eps, double a, double b, double c){
    if (a > b) swap(&a, &b);
    if (b > c) swap(&b, &c);


    if (fabs(c * c - a * a - b * b) < eps)
        return true;
    else
        return false;
}