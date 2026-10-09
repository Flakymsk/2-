#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
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

void print_const(const char *str, const double num){
    printf("%s = %f\n", str, num);
}

int fact_x(const int x){
    int fact = 1;

    for (int i = 2; i <= x; ++i)
        fact *= i;
    
    return fact;
}

bool is_prime_number(const long x) {
    if (x < 2) return false; 
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0)
            return false;
    }
    return true;
}


double lim_e(const double eps){
    double prev_e = 1.0;
    double e = 1.0;
    double count = 1.0;
    do{
        prev_e = e;
        e = (1 + 1/count);
        e = pow(e, count);
        count *= 2.0;
    } while (fabs(e - prev_e) > eps);

    return e;
}

double sequence_e(const double eps){
    double prev_e = 1.0;
    double e = 2.0;
    double fact = 1.0;

    for (int i = 2; fabs(e - prev_e) > eps; ++i){
        prev_e = e;
        fact /= i;
        e += fact;
    }
    
    return e;
}

double equation_e(const double eps){
    double prev_e = 1.0;
    double e = 2.0;

    do{
        prev_e = e;
        e = prev_e - (log(prev_e) - 1.0) * prev_e;
    } while (fabs(e - prev_e) > eps);

    return e;
}

double lim_pi(const double eps){
    double prev_pi = 0.0;
    double pi = 2.0; 
    double count = 1.0;

    do {
        prev_pi = pi;
        double term = (4.0 * count * count) / (4.0 * count * count - 1.0);
        pi *= term;
        
        count += 1.0;
    } while (fabs(pi - prev_pi) > eps);

    return pi;
}

double sequence_pi(const double eps) {
    double prev_pi = 0.0;
    double pi = 0.0;
    double sign = 1.0;
    long n = 0;

    do {
        prev_pi = pi;
        pi += 4.0 * (sign / (2.0 * n + 1.0));
        sign = -sign;

        ++n;
    } while (fabs(pi - prev_pi) > eps);

    return pi;
}

double equation_pi(const double eps) {
    double prev_pi = 0.0;
    double pi = 3.0;

    do {
        prev_pi = pi;
        pi = prev_pi - sin(prev_pi) / cos(prev_pi);
    } while (fabs(pi - prev_pi) > eps);

    return pi;
}

double lim_ln2(const double eps) {
    double prev_ln2 = 0.0;
    double ln2 = 1.0;
    double count = 2.0;

    do {
        prev_ln2 = ln2;
        ln2 = count * (pow(2.0, 1.0 / count) - 1.0);
        count += 1.0;
    } while (fabs(ln2 - prev_ln2) > eps);

    return ln2;
}

double sequence_ln2(const double eps) {
    double prev_ln2 = 1.0 / 1.0;
    double ln2 = prev_ln2 - (1.0 / 2.0);
    double sign = 1.0;

    for (int n = 3; fabs(ln2 - prev_ln2) > eps; ++n) {
        prev_ln2 = ln2;
        ln2 += sign / n;
        sign = -sign;
    }
    
    return ln2;
}

double equation_ln2(const double eps) {
    double prev_ln2;
    double ln2 = 0.5;

    do {
        prev_ln2 = ln2;
        ln2 = prev_ln2 - 1.0 + 2.0 / exp(prev_ln2);
    } while (fabs(ln2 - prev_ln2) > eps);

    return ln2;
}

double lim_sqrt2(const double eps) {
    double prev_x = -0.5; 
    double x = -0.5;

    do {
        prev_x = x;
        x = prev_x - (prev_x * prev_x / 2.0) + 1.0;
    } while (fabs(x - prev_x) > eps);

    return fabs(x); 
}

double sequence_sqrt2(const double eps) {
    double prev_sqrt2 = pow(2.0, pow(2.0, -2.0));
    double sqrt2 = prev_sqrt2 * pow(2.0, pow(2.0, -3.0));

    for (int k = 4; fabs(sqrt2 - prev_sqrt2) > eps; ++k) {
        prev_sqrt2 = sqrt2;
        sqrt2 *= pow(2.0, pow(2.0, -k));
    }
    
    return sqrt2;
}

double equation_sqrt2(const double eps) {
    double prev_sqrt2;
    double sqrt2 = 1.5;

    do {
        prev_sqrt2 = sqrt2;
        sqrt2 = 0.5 * (prev_sqrt2 + 2.0 / prev_sqrt2);
    } while (fabs(sqrt2 - prev_sqrt2) > eps);

    return sqrt2;
}

double lim_gamma(const double eps) {
    double prev_gamma = 0.0;
    double gamma = 0.0;
    double m = 2.0;

    do{
        prev_gamma = gamma;
        double sum = 0.0;
        double C_m_k = 1.0;
        double log_fact_k = 0.0;

        for (double k = 1.0; k <= m; k += 1.0){
            C_m_k *= (m - k + 1.0) / k;
            log_fact_k += log(k);
            double sign = (fmod(k, 2.0) == 0.0) ? 1.0 : -1.0;
            sum += C_m_k * (sign / k) * log_fact_k;
        }

        gamma = sum;
        m += 1.0;
    } while (fabs(gamma - prev_gamma) > eps && m < 50.0);

    return gamma;
}

double sequence_gamma(const double eps) {
    double pi = equation_pi(eps);
    double prev_gamma = 0.0;
    double gamma = -(pi * pi) / 6.0; 
    double k = 2.0;

    long iter = 0;

    do{
        prev_gamma = gamma;
        double root = floor(sqrt(k));
        gamma += (1.0 / (root * root)) - (1.0 / k);

        k += 1.0;
        ++iter;
    } while (fabs(gamma - prev_gamma) > eps || iter < 1000000);
    
    return gamma;
}

double equation_gamma(const double eps) {
    double prev_gamma = 0.0;
    double gamma = 0.0;
    double t = 2.0;

    do {
        prev_gamma = gamma;
        double prod = 1.0;

        for (int p = 2; p <= (int)t; ++p) {
            if (is_prime_number(p)) {
                prod *= ((double)p - 1.0) / (double)p;
            }
        }

        double A = log(t) * prod;
        gamma = -log(A);

        t += 1.0;
    } while (fabs(gamma - prev_gamma) > eps && t < 20000.0);

    return gamma;
}

int main(int argc,char *argv[]){
    double eps;
    status_code msg;
    if ((msg = parse_args(argc, argv, &eps)) != SUCCESS){
        print_error_message(msg);
        return 1;
    }

    double num1 = lim_e(eps);
    double num2 = sequence_e(eps);
    double num3 = equation_e(eps);

    print_const("lim e", num1);
    print_const("sequence e", num2);
    print_const("equation e", num3);

    num1 = lim_pi(eps);
    num2 = sequence_pi(eps);
    num3 = equation_pi(eps);

    print_const("lim pi", num1);
    print_const("sequence pi", num2);
    print_const("equation pi", num3);

    num1 = lim_ln2(eps);
    num2 = sequence_ln2(eps);
    num3 = equation_ln2(eps);

    print_const("lim ln2", num1);
    print_const("sequence ln2", num2);
    print_const("equation ln2", num3);

    num1 = lim_sqrt2(eps);
    num2 = sequence_sqrt2(eps);
    num3 = equation_sqrt2(eps);

    print_const("lim sqrt2", num1);
    print_const("sequence sqrt2", num2);
    print_const("equation sqrt2", num3);

    num1 = lim_gamma(eps);
    num2 = sequence_gamma(eps);
    num3 = equation_gamma(eps);

    print_const("lim gamma", num1);
    print_const("sequence gamma", num2);
    print_const("equation gamma", num3);

}