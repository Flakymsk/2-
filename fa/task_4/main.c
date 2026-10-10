#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "../utils.h"
#include "func.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, ""); 

    char flag;
    char *input_path = NULL;
    char output_name[256] = {0};
    status_code msg;

    if ((msg = parse_args(argc, argv, &flag, &input_path, output_name)) != SUCCESS) {
        print_error_message(msg);
        return 1;
    }

    FILE *file_input = fopen(input_path, "r");
    if (file_input == NULL) {
        print_error_message(ERR_OPEN_FILE);
        return 1;
    }

    FILE *file_output = fopen(output_name, "w");
    if (file_output == NULL) {
        print_error_message(ERR_OPEN_FILE);
        fclose(file_input);
        return 1;
    }

    switch (flag) {
        case 'd':
            write_file_ignore_arabic(file_input, file_output);
            break;
        case 'i':
            write_amount_latin(file_input, file_output);
            break;
        case 's':
            write_amount_non_latin_arabic_space(file_input, file_output);
            break;
        case 'a':
            write_non_num_hex(file_input, file_output);
            break;
        default:
            print_error_message(ERR_WRONG_FLAG);
            fclose(file_input);
            fclose(file_output);
            return 1;
    }

    fclose(file_input);
    fclose(file_output);
    return 0;
}
