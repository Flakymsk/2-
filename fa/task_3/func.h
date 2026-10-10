#ifndef FUNC3
#define FUNC3
#include "../utils.h"

status_code parse_args(int argc, char *argv[], const char flag, double *arr_d, long *arr_l);
void swap(double *a, double *b);
void print_bool(const bool x);
void swap_arr(double *arr, int i, int j);
void solve_quad_equation(const double a, const  double b, const double c, const double eps);
void check_quad_coeffs(double *arr, int iter, const double eps);
bool check_triangle_sides (const double eps, double a, double b, double c);


#endif