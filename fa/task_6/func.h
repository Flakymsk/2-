#ifndef func_6
#define func_6
#include "../utils.h"
#include <stdbool.h>

status_code parse_flag(int argc, char* argv[], char *flag);
status_code parse_task1(int argc, char *argv[], double coords[8]);
status_code parse_task2(int argc, char *argv[], double *x, double coeffs[4]);
status_code parse_task3(int argc, char *argv[], long *base, const char *strings[3]);
status_code parse_task4(int argc, char *argv[], double nums[3]);
status_code parse_task5(int argc, char *argv[], double *x, long *pow_val);
status_code parse_task6(int argc, char *argv[], double *a, double *b, double *eps);
bool is_figure_convex(const long amount, ...);
double count_polynomial(const double x, const long pow, ...);
bool is_kaprekar(const long num, const long base);
status_code find_kaprekar_nums(char* str_ans[], const long base, const long count, ...);
double geometric(const long count, ...);
double fast_pow(const double x, const long pow);
double equation_1(double x);
double equation_2(double x);
double solve_dichotomy(double a, double b, const double eps, double (*func)(double));
#endif
