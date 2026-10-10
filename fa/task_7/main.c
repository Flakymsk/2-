#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../utils.h"
#include "func.h"

int main(int argc, char *argv[]){
    char choice;
    status_code msg;

    if ((msg = parse_args(argc, argv, &choice)) != SUCCESS){
        print_error_message(msg);
        return 1;
    }

    if (choice == 'r'){
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

        write_mixed_lexemes(file1, file2, file3);

        fclose(file1);
        fclose(file2);
        fclose(file3);
    } else if (choice == 'a'){
        FILE *readfile = fopen(argv[2], "r");
        FILE *writefile = fopen(argv[3], "w");

        if ((msg = check_opening_files(2, readfile, writefile)) != SUCCESS){
            print_error_message(msg);
            if (readfile) fclose(readfile);
            if (writefile) fclose(writefile);
            return 1;
        }

        write_modified_lexemes(readfile, writefile);

        fclose(readfile);
        fclose(writefile);
    }

    return 0;
}
