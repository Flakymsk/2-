#ifndef func_10
#define func_10
#include "../utils.h"

status_code parse_base(int argc, char *argv[], long *base);
status_code parse_number(const char *arg, long *number, const long base);
void print_number_base_n(long number, int n);
void proceed_number(const long number, long *max_val, long *sum);

#endif