#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include "../utils.h"

status_code parse_args(int argc, char *argv[], char *flag){
    if (argc < 4)
        return ERR_WRONG_ARG_COUNT;

    if ((argv[1][0] != '-' && argv[1][0] != '/') || strlen(argv[1]) != 2)
        return ERR_WRONG_FLAG;

    *flag = argv[1][1];

    if (*flag == 'r') {
        if (argc != 5)
            return ERR_WRONG_ARG_COUNT;
        if (strcmp(argv[2], argv[4]) == 0 || strcmp(argv[3], argv[4]) == 0)
            return ERR_INVALID_PATHS;
    } else if (*flag == 'a') {
        if (argc != 4)
            return ERR_WRONG_ARG_COUNT;
        if (strcmp(argv[2], argv[3]) == 0)
            return ERR_INVALID_PATHS;
    } else {
        return ERR_WRONG_FLAG;
    }

    return SUCCESS;
}

status_code check_opening_files(int amount, ...){
    va_list args;
    va_start(args, amount);

    for (int i = 0; i < amount; ++i) {
        FILE *f = va_arg(args, FILE*);
        if (f == NULL) {
            va_end(args);
            return ERR_OPEN_FILE;
        }
    }

    va_end(args);
    return SUCCESS;
}

void fputc_base_n(FILE *writefile, int c, int n){
    if (c >= n) {
        fputc_base_n(writefile, c / n, n);
    }
    int digit = c % n;
    if (digit < 10)
        fprintf(writefile, "%d", digit);
    else
        fprintf(writefile, "%c", 'A' + digit - 10);
}

void swap_files(FILE **a, FILE **b){
    FILE *temp = *a;
    *a = *b;
    *b = temp;
}

void write_mixed_lexemes(FILE *file1, FILE *file2, FILE *file3){
    int c;
    FILE *readfile = file1;
    FILE *waitfile = file2;
    bool in_word = false;
    bool has_content = false;

    while ((c = fgetc(readfile)) != EOF) {
        if (isspace(c)) {
            if (in_word) {
                in_word = false;
                int next_check = fgetc(waitfile);
                if (next_check != EOF) {
                    ungetc(next_check, waitfile);
                    swap_files(&readfile, &waitfile);
                }
            }
        } else {
            if (!in_word && has_content)
                fputc(' ', file3);
        
            in_word = true;
            has_content = true;
            fputc(c, file3);
        }
    }

    if (waitfile != NULL) {
        readfile = waitfile;
        in_word = false;
        while ((c = fgetc(readfile)) != EOF) {
            if (isspace(c)) {
                if (in_word) 
                    in_word = false;
            } else {
                if (!in_word && has_content) {
                    fputc(' ', file3);
                }
                in_word = true;
                has_content = true;
                fputc(c, file3);
            }
        }
    }
}

void write_modified_lexemes(FILE *readfile, FILE *writefile){
    int count = 1, c;
    bool in_word = false;
    bool has_content = false;

    while ((c = fgetc(readfile)) != EOF) {
        if (isspace(c)) {
            if (in_word) {
                in_word = false;
                count++;
            }
        } else {
            if (!in_word && has_content)
                fputc(' ', writefile);
        
            in_word = true;
            has_content = true;

            if (count % 10 == 0) {
                if (c >= 'A' && c <= 'Z') c += 32;
                fputc_base_n(writefile, c, 4);
            } else if (count % 2 == 0) {
                if (c >= 'A' && c <= 'Z') c += 32;
                fputc(c, writefile);
            } else if (count % 5 == 0) 
                fputc_base_n(writefile, c, 8);
            else
                fputc(c, writefile);
        }
    }
}
