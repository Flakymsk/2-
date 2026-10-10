#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <wctype.h>
#include <wchar.h>
#include <sys/stat.h>
#include "../utils.h"

status_code parse_args(int argc, char *argv[], char *flag, char **input_path, char *output_name) {
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

    struct stat stat_in, stat_out;
    if (stat(*input_path, &stat_in) == 0 && stat(output_name, &stat_out) == 0) {
        if (stat_in.st_ino == stat_out.st_ino && stat_in.st_dev == stat_out.st_dev)
            return ERR_INVALID_PATHS;
    }

    return SUCCESS;
}

void write_file_ignore_arabic(FILE *file_input, FILE *file_output) {
    wint_t c;

    while ((c = fgetwc(file_input)) != WEOF) {
        if (iswdigit(c))
            continue;
        
        fputwc(c, file_output);
    }
}

void write_amount_latin(FILE *file_input, FILE *file_output) {
    wint_t c;
    int count = 0;
    bool has_chars = false;

    while ((c = fgetwc(file_input)) != WEOF) {
        has_chars = true;
        
        if (c == L'\r')
            continue;

        if (c == L'\n') {
            fprintf(file_output, "%d\n", count);
            count = 0;
            has_chars = false;
            continue;
        }

        if ((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z'))
            ++count;
    }

    if (has_chars) {
        fprintf(file_output, "%d\n", count);
    }
}

void write_amount_non_latin_arabic_space(FILE *file_input, FILE *file_output) {
    wint_t c;
    int count = 0;
    bool has_chars = false;

    while ((c = fgetwc(file_input)) != WEOF) {
        has_chars = true;
        
        if (c == L'\r')
            continue;

        if (c == L'\n') {
            fprintf(file_output, "%d\n", count);
            count = 0;
            has_chars = false;
            continue;
        }

        if (!((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z')) && 
            !(c >= L'0' && c <= L'9') && c != L' ')
            ++count;
    }

    if (has_chars) {
        fprintf(file_output, "%d\n", count);
    }
}

void fputc_hex(FILE *file_output, wint_t c) {
    if (c > 15) {
        fputc_hex(file_output, c / 16);
    }

    int digit = c % 16;
    if (digit < 10)
        fprintf(file_output, "%d", digit);
    else
        fprintf(file_output, "%c", 'A' + digit - 10);
}

void write_non_num_hex(FILE *file_input, FILE *file_output) {
    wint_t c;
    bool need_space = false;

    while ((c = fgetwc(file_input)) != WEOF) {
        if (c == L'\r')
            continue;

        if (c == L'\n') {
            fputwc(L'\n', file_output);
            need_space = false;
            continue;
        }

        if (c >= L'0' && c <= L'9') {
            fputwc(c, file_output);
            need_space = false;
        } else {
            if (need_space) {
                fputwc(L' ', file_output);
            }
            fputc_hex(file_output, c);
            need_space = true;
        }
    }
}
