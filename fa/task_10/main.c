#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "func.h"
#include "../utils.h"

int main(int argc, char *argv[]){
    long base;
    status_code msg;

    if ((msg = parse_base(argc, argv, &base)) != SUCCESS){
        print_error_message(msg);
        return 1;
    }

    long number, max_val = 0, sum = 0;
    bool has_numbers = false;
    char input_buf[256];

    while (scanf("%255s", input_buf) == 1){
        if (strcmp(input_buf, "Stop") == 0)
            break;

        if ((msg = parse_number(input_buf, &number, base)) != SUCCESS){
            print_error_message(msg);
            return 1;
        }

        has_numbers = true;
        proceed_number(number, &max_val, &sum);
    }

    if (!has_numbers){
        printf("no numbers\n");
        return 0;
    }

    printf("Max absolute:\n");
    for (int j = 9; j <= 36; j += 9){
        printf("Base %d: ", j);
        print_number_base_n(max_val, j);
        printf("\n");
    }

    printf("Sum:\n");
    for (int j = 9; j <= 36; j += 9){
        printf("Base %d: ", j);
        print_number_base_n(sum, j);
        printf("\n");
    }

    return 0;
}
