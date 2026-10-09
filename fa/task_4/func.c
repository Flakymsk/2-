#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

status_code parse_file_arguments(int argc, char *argv[], char *flag, char **input_path, char *output_name){
    if (argc != 3 && argc != 4)
        return ERR_WRONG_ARG_COUNT;

    if (argv[1][0] != '-' && argv[1][0] != '/')
        return ERR_WRONG_FLAG;

    bool has_n = (argv[1][1] == 'n');

    if (has_n) {
        if (argc != 4 || strlen(argv[1]) != 3)
            return ERR_WRONG_ARG_COUNT;

        *flag = argv[1][2];
        strcpy(output_name, argv[3]);
    } else {
        if (argc != 3 || strlen(argv[1]) != 2)
            return ERR_WRONG_ARG_COUNT;

        *flag = argv[1][1];
        sprintf(output_name, "out_%s", argv[2]);
    }

    *input_path = argv[2];

    if (strcmp(*input_path, output_name) == 0)
        return ERR_INVALID_PATHS;

    return SUCCESS;
}

void write_file_ignore_arabic(FILE *file_input, FILE *file_output){
    int c;
    
    while ((c = getc(file_input)) != EOF){
        if (isdigit(c))
            continue;
        
        fputc(c, file_output);
    }
}

void write_amount_latin(FILE *file_input, FILE *file_output){
    int c;
    int count = 0;
    bool has_chars = false;

    while ((c = fgetc(file_input)) != EOF){
        has_chars = true;
        if (c == '\n'){
            fprintf(file_output, "%d\n", count);
            count = 0;
            has_chars = false;
            continue;
        }

        if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')
            ++count;
    }

    if (has_chars){
        fprintf(file_output, "%d\n", count);
    }
}

void write_amount_non_latin_arabic_space(FILE *file_input, FILE *file_output){
    int c;
    int count = 0;
    bool has_chars = false;

    while ((c = fgetc(file_input)) != EOF){
        has_chars = true;
        if (c == '\n'){
            fprintf(file_output, "%d\n", count);
            count = 0;
            has_chars = false;
            continue;
        }

        if (!(c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z') && 
        !(c >= '0' && c <= '9') && c != ' ')
            ++count;
    }

    if (has_chars){
        fprintf(file_output, "%d\n", count);
    }
}

void fputc_hex(FILE *file_output, int c){
    if (c > 15){
        fputc_hex(file_output, c / 16);
    }

    int digit = c % 16;

    if (digit < 10)
        fprintf(file_output, "%d", digit);
    else
        fprintf(file_output, "%c", 'A' + digit - 10);
}

void write_non_num_hex(FILE *file_input, FILE *file_output){
    int c;
    bool need_space = false;

    while ((c = fgetc(file_input)) != EOF){
        if (c == '\n'){
            fputc('\n', file_output);
            need_space = false;
            continue;
        }

        if (c >= '0' && c <= '9'){
            fputc(c, file_output);
            need_space = false;
        } else{
            if (need_space) {
                fputc(' ', file_output);
            }
            fputc_hex(file_output, c);
            need_space = true;
        }
    }
}
