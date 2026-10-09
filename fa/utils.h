#ifndef UTILS_H
#define UTILS_H

typedef enum {
    SUCCESS = 0,
    ERR_WRONG_ARG_COUNT,
    ERR_WRONG_FLAG,
    ERR_INVALID_NUMBER,
    ERR_RANGE_MISMATCH,
    ERR_MEMORY_ALLOC,
    ERR_INVALID_PATHS,
    ERR_OPEN_FILE,
} status_code;

void print_error_message(status_code code);

#endif
