#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

bool is_figure_convex(int amount, ...){
    va_list args;
    va_start(args, amount);

    double xy[2] = va_arg(args, double);
}

double count_polynomial(double x, int pow, ...){
    va_list args;
    va_start(args, pow);

    double result = va_arg(args, double);

    for (int i = 0; i < pow; ++i)
        result = result * x + va_arg(args, double);

    va_end(args);

    return result;
}

double geometric(int count, ...){
    va_list args;
    va_start(args, count);

    double mul = 1.0;

    for (int i = 0; i < count; ++i){
        mul *= va_arg(args, double);
    }

    va_end(args);

    return pow(mul, 1.0 / count);
}

double fast_pow(double x, int pow){
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

double solve_dichotomy(double a, double b, double eps, double (*func)(double)){
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

int main(){
    printf("%f\n", solve_dichotomy(-100, 100, 0.0000001, equation_1));
    printf("%f\n", solve_dichotomy(-100, 100, 0.0000001, equation_2));

}