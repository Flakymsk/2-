#include <stdio.h>
#include "func.h"

int main(int argc, char *argv[]){
    long base;
    parse_base(argc, argv, &base);

    long number, max_val, sum = 0;

    for (int i = 2; argv[i] != "Stop"; ++i){
        parse_number(argv[i], &number, base);
        proceed_number(number, &max_val, &sum);

        for (int j = 9; j <= 36; j += 9)
            print_number_base_n(number, j);
    }
}