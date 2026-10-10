#ifndef func_4
#define func_4

#include <stdio.h>
#include "../utils.h"

status_code parse_args(int argc, char *argv[], char *flag, char **input_path, char *output_name);
void write_file_ignore_arabic(FILE *file_input, FILE *file_output);
void write_amount_latin(FILE *file_input, FILE *file_output);
void write_amount_non_latin_arabic_space(FILE *file_input, FILE *file_output);
void write_non_num_hex(FILE *file_input, FILE *file_output);


#endif
