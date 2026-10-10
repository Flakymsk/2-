#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include "../utils.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

status_code check_opening_files(int amount, ...){
    va_list files;
    va_start(files, amount);
    
    for (int i = 0; i < amount; ++i){
        FILE *f = va_arg(files, FILE*);
        
        if (!f){
            va_end(files);
            return ERR_OPEN_FILE;
        }
    }
    
    va_end(files);
    
    return SUCCESS;
}

void process_lexeme(FILE *writefile, const char *lex, int idx){
    int base = 2;
    for (int i = 0; i < idx; ++i){
        if (isdigit(lex[i]))
            base = max(base, lex[i] - '0' + 1);
        else if (isalpha(lex[i]))
            base = max(base, toupper(lex[i]) - 'A' + 11);
    }

    int start = 0;
    while (start < idx && lex[start] == '0')
        ++start;

    if (start == idx){
        fprintf(writefile, "0 2 0\n");
    } else {
        long long val10 = 0;
        for (int i = start; i < idx; ++i){
            int v = isdigit(lex[i]) ? (lex[i] - '0') : (toupper(lex[i]) - 'A' + 10);
            val10 = val10 * base + v;
        }
        fprintf(writefile, "%s %d %lld\n", &lex[start], base, val10);
    }
}

void write_converted_bases(FILE *readfile, FILE *writefile){
    char lex[256];
    int idx = 0;
    int c;

    while ((c = fgetc(readfile)) != EOF){
        if (isspace(c)){
            if (idx > 0){
                lex[idx] = '\0';
                process_lexeme(writefile, lex, idx);
                idx = 0;
            }
        } else {
            if (idx < 255)
                lex[idx++] = c;
        }
    }

    if (idx > 0){
        lex[idx] = '\0';
        process_lexeme(writefile, lex, idx);
    }
}
