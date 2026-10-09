#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../utils.h"


status_code parse_args(int argc, char *argv[], double *eps){
    if (argc != 2)
        return ERR_WRONG_ARG_COUNT;

    char *endptr1;

    *eps = strtod(argv[1], &endptr1);

    if (*eps == HUGE_VAL || *eps <= 0.0 ||
        *endptr1 != '\0' || endptr1 == argv[1])
        return ERR_INVALID_NUMBER;
    
    return SUCCESS;
}

double integrate_a(const double eps){
    int n = 2;
    double prev_sum = 0.0;
    double sum = 0.0;

    do{
        prev_sum = sum;
        double dx = 1.0 / n;
        sum = 0.0;

        for (int i = 0; i < n; ++i){
            double x_mid = (i + 0.5) * dx;
            sum += log(1.0 + x_mid) / x_mid;
        }

        sum *= dx;
        n *= 2;

    }while (fabs(sum - prev_sum) > eps);

    return sum;
}

double integrate_b(const double eps){
    int n = 2;
    double prev_sum = 0.0;
    double sum = 0.0;

    do{
        prev_sum = sum;
        double dx = 1.0 / n;
        sum = 0.0;

        for (int i = 0; i < n; ++i){
            double x_mid = (i + 0.5) * dx;
            sum += exp(-x_mid * x_mid / 2.0);
        }

        sum *= dx;
        n *= 2;

    }while (fabs(sum - prev_sum) > eps);

    return sum;
}

double integrate_c(const double eps){
    int n = 2;
    double prev_sum = 0.0;
    double sum = 0.0;

    do{
        prev_sum = sum;
        double dx = 1.0 / n;
        sum = 0.0;

        for (int i = 0; i < n; ++i){
            double x_mid = (i + 0.5) * dx;
            sum += log(1.0 / (1.0 - x_mid));
        }

        sum *= dx;
        n *= 2;

    }while (fabs(sum - prev_sum) > eps);

    return sum;
}

double integrate_d(const double eps){
    int n = 2;
    double prev_sum = 0.0;
    double sum = 0.0;

    do{
        prev_sum = sum;
        double dx = 1.0 / n;
        sum = 0.0;

        for (int i = 0; i < n; ++i){
            double x_mid = (i + 0.5) * dx;
            sum += pow(x_mid, x_mid);
        }

        sum *= dx;
        n *= 2;

    }while (fabs(sum - prev_sum) > eps);

    return sum;
}

int main(int argc, char *argv[]){
    double eps, integral;

    status_code msg;
    if ((msg = parse_args(argc, argv, &eps)) != SUCCESS){
        print_error_message(msg);
        return 1;
    }

    double (*integrals[])(const double) = {integrate_a, integrate_b, integrate_c, integrate_d};

    for (int i = 0; i < 4; ++i){
        integral = integrals[i](eps);
        printf("integral_%c = ", i + 'a');

        if (integral == HUGE_VAL)
            printf("HUGE_VAL ");

        printf("%f\n", integral);
    }
    
        
}