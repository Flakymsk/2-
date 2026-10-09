#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void print_error_message(status_code code) {
    switch (code) {
        case ERR_WRONG_ARG_COUNT:
            printf("Error: Invalid number of arguments.\n");
            break;
        case ERR_WRONG_FLAG:
            printf("Error: Invalid flag input.\n");
            break;
        case ERR_INVALID_NUMBER:
            printf("Error: Arguments must be valid.\n");
            break;
        case ERR_RANGE_MISMATCH:
            printf("Error: Parameter 'a' cannot be greater than 'b'.\n");
            break;
        case ERR_MEMORY_ALLOC:
            printf("Error: Failed to allocate dynamic memory.\n");
            break;
        case ERR_OPEN_FILE:
            printf("Error: Failed to open file\n");
            break;
        default:
            break;
    }
}