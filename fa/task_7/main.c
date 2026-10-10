#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "../utils.h"
#include "func.h"

int main(int argc, char *argv[]){
    status_code msg;

    if (argc < 4){
        print_error_message(ERR_WRONG_ARG_COUNT);
        return 1;
    }

    if (!strcmp(argv[1], "-r") || !strcmp(argv[1], "/r")){
        FILE *file1 = fopen(argv[2], "r");
        FILE *file2 = fopen(argv[3], "r");
        FILE *file3 = fopen(argv[4], "w");

        if ((msg = check_opening_files(3, file1, file2, file3)) != SUCCESS){
            print_error_message(msg);

            if (file1) fclose(file1);
            if (file2) fclose(file2);
            if (file3) fclose(file3);

            return 1;
        }

        int c;
        FILE *readfile = file1;
        FILE *waitfile = file2;
        bool in_word = true;

        while ((c = fgetc(readfile)) != EOF){
            if (isspace(c)){
                in_word = false;
                fputc(' ', file3);

                swap_files(&readfile, &waitfile);
            } else{
                in_word = true;
                fputc(c, file3);
            }
        }
        
        if (waitfile != NULL){
            readfile = waitfile;
            in_word = true;

            while ((c = fgetc(readfile)) != EOF){
                if (isspace(c)){
                    if (in_word)
                        fputc(' ', file3);

                    in_word = false;
                } else{
                    in_word = true;
                    fputc(c, file3);
                }
            }
                
        }

        fclose(file1);
        fclose(file2);
        fclose(file3);
    } else if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "/a")){
        FILE *readfile = fopen(argv[2], "r");
        FILE *writefile = fopen(argv[3], "w");

        if ((msg = check_opening_files(2, readfile, writefile)) != SUCCESS){
            print_error_message(msg);

            if (readfile) fclose(readfile);
            if (writefile) fclose(writefile);

            return 1;
        }

        int count = 1, c;
        bool in_word = false;

        while ((c = fgetc(readfile)) != EOF){
                if (isspace(c)){
                    if (in_word) {
                        fputc(' ', writefile);
                        in_word = false;
                        ++count;
                    }
                } else{
                    in_word = true;
                    if (count % 10 == 0){
                        if (c >= 'A' && c <= 'Z')
                            c += 32;
        
                        fputc_base_n(writefile, c, 4);
                    } else if (count % 2 == 0){
                        if (c >= 'A' && c <= 'Z')
                            c += 32;
                        fputc(c, writefile);
                    } else if (count % 5 == 0)
                        fputc_base_n(writefile, c, 8);
                    else
                        fputc(c, writefile);
                    
                }
        }
        
        fclose(readfile);
        fclose(writefile);
    } else{
        print_error_message(ERR_WRONG_FLAG);
        return 1;
    }

    return 0;
}
