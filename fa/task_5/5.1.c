#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../utils.h"
#include <math.h>

#define MAX_ITERATIONS 1000000

status_code parse_args(int argc, char *argv[], double *x, double *eps){
    if (argc != 3)
        return ERR_WRONG_ARG_COUNT;

    char *endptr1;
    *x = strtod(argv[1], &endptr1);

    if (*x == HUGE_VAL || *x == -HUGE_VAL ||
        *endptr1 != '\0' || endptr1 == argv[1])
        return ERR_INVALID_NUMBER;

    *eps = strtod(argv[2], &endptr1);

    if (*eps == HUGE_VAL || *eps <= 0.0 ||
        *endptr1 != '\0' || endptr1 == argv[2])
        return ERR_INVALID_NUMBER;
    
    return SUCCESS;
}

double sum_a(const double x, const double eps){
    double sum = 1.0;
    double t = 1.0;
    int n = 1;
    int iter = 0;

    while (t > eps){
        t *= x / n;
        sum += t;
        ++n;

        ++iter;
        if (iter > MAX_ITERATIONS)
            return HUGE_VAL;
    }

    return sum;
}

double sum_b(const double x, const double eps){
    double sum = 1.0;
    double t = 1.0;
    int n = 1;
    int iter = 0;

    while (fabs(t) > eps){
        t *= -x * x / (( 2 * n - 1) * (2 * n));
        sum += t;
        ++n;
        
        ++iter;
        if (iter > MAX_ITERATIONS)
            return HUGE_VAL;
    }

    return sum;
}

double sum_c(const double x, const double eps){
    double sum = 1.0;
    double t = 1.0;
    int n = 1;
    int iter = 0;

    while(t > eps){
        t *= 9.0 * n * n * x * x / ((3 * n - 2) * (3 * n - 1));
        sum += t;
        ++n;

        ++iter;
        if (iter > MAX_ITERATIONS)
            return HUGE_VAL;
    }

    return sum;
}

double sum_d(const double x, const double eps){
    double sum = -0.5 * x * x;
    double t = sum;
    int n = 2;
    int iter = 0;

    while (fabs(t) > eps){
        t *= -x * x * (2.0 * n - 1) / (2 * n);
        sum += t;
        ++n;
        
        ++iter;
        if (iter > MAX_ITERATIONS)
            return HUGE_VAL;
    }

    return sum;
}

int main(int argc, char *argv[]){
    double x, eps, sum;
    status_code msg;
    if ((msg = parse_args(argc, argv, &x, &eps)) != SUCCESS){
        print_error_message(msg);
        return 1;
    }
    
    double (*sums[])(const double, const double) = {sum_a, sum_b, sum_c, sum_d};

    for (int i = 0; i < 4; ++i){
        sum = sums[i](x, eps);
        printf("sum_%c = ", i + 'a');

        if (sum == HUGE_VAL)
            printf("HUGE_VAL ");

        printf("%f\n", sum);
    }
        

}