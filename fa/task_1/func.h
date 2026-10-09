#ifndef FUNC_1
#define FUNC_1
#include "../utils.h"

status_code parse_args(int argc, char *argv[], long *num, char *c);
void print_bool(const bool x);
void print_x(const long x);
void print_str(const char *str);
void print_chars(const char *str);
void print_arr(const long *arr, const int amount);
long* get_natural_numbers_multiples_x(const long x, int *amount);
bool is_prime_number(const long x);
char* count_num_hex(unsigned long x);
void print_table_pows(const long x);
long sum_from_1_to_x(const long x);
long fact_x(const long x);
#endif