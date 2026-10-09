#include <stdio.h>
#include <stdbool.h>
#include "../utils.h"

void print_bool(const bool x){
    printf("%s\n", (x == true ? "true" : "false"));
}

int main(int argc, char *argv[]){
    char flag;
    status_code msg;

    if ((msg = parse_flag(argc, argv, &flag)) != SUCCESS){
        print_error_message(msg);
        
        return 1;
    }

    switch (flag){
    case 'q':{
        double arr[4];
        if ((msg = parse_args(argc, argv, flag, arr, NULL)) != SUCCESS){
            print_error_message(msg);
        
            return 1;
        }
        double arr_coeffs[3] = {arr[1], arr[2], arr[3]};
        check_quad_coeffs(arr_coeffs, 0, arr[0]);
        break;
    }
    case 'm':{
        long arr[2];
        if ((msg = parse_args(argc, argv, flag, NULL, arr)) != SUCCESS){
            print_error_message(msg);
        
            return 1;
        }

        long a = arr[0];
        long b = arr[1];

        if (a % b == 0)
            printf("yes");
        else
            printf("no");

        break;
    }
    case 't':
        double arr[4];
        if ((msg = parse_args(argc, argv, flag, arr, NULL)) != SUCCESS){
            print_error_message(msg);
        
            return 1;
        }

        print_bool(check_triangle_sides(arr[0], arr[1], arr[2], arr[3]));
        break;

    default:
        print_error_message(ERR_WRONG_FLAG);
        return 1;
    }
}