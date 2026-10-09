#include <stdbool.h>
#include "func.h"
#include "../utils.h"

int main(int argc, char *argv[]){
    long x;
    char choice;
    status_code msg;
    if ((msg = parse_args(argc, argv, &x, &choice)) != SUCCESS){
        print_error_message(msg);
        return 1;
    }

    switch (choice){
    case 'h':{
        int amount = 0;
        long* result = get_natural_numbers_multiples_x(x, &amount);
        print_arr(result, amount);
        break;
    }
    case 'p':{
        bool is_prime = is_prime_number(x);
        print_bool(is_prime);
        break;
    }
    case 's':{
        char *str = count_num_hex(x);
        print_chars(str);
        break;
    }
    case 'e':
        if (x > 10){
            print_error_message(ERR_INVALID_NUMBER);
            return 1;
        }

        print_table_pows(x);
        break;
    case 'a':{
        long sum = sum_from_1_to_x(x);
        print_x(sum);
        break;
    }
    case 'f':{
        long fact = fact_x(x);
        print_x(fact);
        break;
    }
    
    default:
        print_error_message(ERR_WRONG_FLAG);
        return 1;
    }
}