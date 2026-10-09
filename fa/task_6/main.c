#include <stdio.h>
#include <math.h>
#include "func.h"

int main(int argc, char* argv[]){
    char flag;
    status_code msg;

    if ((msg = parse_flag(argc, argv, &flag)) != SUCCESS){
        print_error_message(msg);
        return 1;
    }

    switch (flag){
        case '1': {
            double coords[8];

            if ((msg = parse_task1(argc, argv, coords)) != SUCCESS) {
                print_error_message(msg);
                return 1;
            }

            if (is_figure_convex(4, coords[0], coords[1], coords[2], coords[3], coords[4], coords[5], coords[6], coords[7])) {
                printf("Figure is convex\n");
            } else {
                printf("Figure is not convex\n");
            }
            break;
        }
        case '2': {
            double x;
            double coeffs[4];

            if ((msg = parse_task2(argc, argv, &x, coeffs)) != SUCCESS) {
                print_error_message(msg);
                return 1;
            }

            double res = count_polynomial(x, 3, coeffs[0], coeffs[1], coeffs[2], coeffs[3]);
            printf("Polynomial result: %f\n", res);
            break;
        }
        case '3': {
            long base;
            const char *strings[3];
            char *str_ans[4];

            if ((msg = parse_task3(argc, argv, &base, strings)) != SUCCESS) {
                print_error_message(msg);
                return 1;
            }

            msg = find_kaprekar_nums(str_ans, base, 3, strings[0], strings[1], strings[2]);
            if (msg != SUCCESS) {
                print_error_message(msg);
                return 1;
            }

            if (str_ans[0] == NULL)
                printf("no Kaprekar numbers\n");
            else{
                printf("Kaprekar nums\n");

                for (int i = 0; str_ans[i] != NULL; ++i)
                    printf("%s\n", str_ans[i]);
            }
            break;
        }
        case '4': {
            double nums[3];

            if ((msg = parse_task4(argc, argv, nums)) != SUCCESS) {
                print_error_message(msg);
                return 1;
            }

            double res = geometric(3, nums[0], nums[1], nums[2]);
            printf("Geometric mean: %f\n", res);
            break;
        }
        case '5':{
            double x;
            long pow_val;
            
            if ((msg = parse_task5(argc, argv, &x, &pow_val)) != SUCCESS) {
                print_error_message(msg);
                return 1;
            }
            
            printf("%f ^ %ld = %f\n", x, pow_val, fast_pow(x, pow_val));
            break;
        }
        case '6': {
            double a, b, eps;
            
            if ((msg = parse_task6(argc, argv, &a, &b, &eps)) != SUCCESS){
                print_error_message(msg);
                return 1;
            }
    
            double root1 = solve_dichotomy(a, b, eps, equation_1);
            if (isnan(root1))
                printf("No roots fo equation 1\n");
            else
                printf("Root for equation 1: %f\n", root1);
            

            double root2 = solve_dichotomy(a, b, eps, equation_2);
            if (isnan(root2))
                printf("No roots fo equation 2\n");
            else 
                printf("Root for equation 2: %f\n", root2);
            
        break;
        }
    }
}