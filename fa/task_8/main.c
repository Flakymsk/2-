#include <stdio.h>
#include "func.h"
#include "../utils.h"

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

    write_converted_bases(readfile, writefile);

    fclose(readfile);
    fclose(writefile);
    return 0;
}
