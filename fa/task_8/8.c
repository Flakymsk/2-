#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
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

int main(int argc, char *argv[]){
    status_code msg;

    if (argc != 3){
        print_error_message(ERR_WRONG_ARG_COUNT);
        return 1;
    }

    FILE *readfile = fopen(argv[1], "r");
    FILE *writefile = fopen(argv[2], "w");

    if ((msg = check_opening_files(2, readfile, writefile)) != SUCCESS){
        print_error_message(msg);
        if (readfile) fclose(readfile);
        if (writefile) fclose(writefile);

        return 1;
    }

    int c, base = 0;
    bool in_word = false;

    while ((c = fgetc(readfile)) != EOF){
        if (isspace(c)){
            if (in_word)
                fprintf(writefile, " %d\n", base);

            base = 2;
            in_word = false;
        } else{
            if (isdigit(c)){
                in_word = true;
                fputc(c, writefile);
                        
                base = max(base, c - '0' + 1);
            } else if (isalpha(c)){
                in_word = true;
                c = toupper(c);
                fputc(c, writefile);

                base = max(base, c - 'A' + 11);
            }
        }
    }
    if (in_word)
        fprintf(writefile, " %d\n", base);

    fclose(readfile);
    fclose(writefile);
}