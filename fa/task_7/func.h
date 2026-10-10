#ifndef func_7
#define func_7
#include "../utils.h"

status_code parse_args(int argc, char *argv[], char *flag);
status_code check_opening_files(int amount, ...);
void fputc_base_n(FILE *writefile, int c, int n);
void swap_files(FILE **a, FILE **b);
void write_mixed_lexemes(FILE *file1, FILE *file2, FILE *file3);
void write_modified_lexemes(FILE *readfile, FILE *writefile);

#endif
