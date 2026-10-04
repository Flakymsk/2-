#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

void write_num(int32_t file, int32_t num) {
    if (num < 0) {
        write(file, "-", 1);
        num = -num;
    }
    if (num >= 10) {
        write_num(file, num / 10);
    }
    char digit = (num % 10) + '0';
    write(file, &digit, 1);
}

int main(int argc, char *argv[]){
    char buf[4096];
    ssize_t bytes;

    int32_t file = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);

    if (file == -1){
        char msg[] = "error opening file";
        write(2, msg, sizeof(msg) - 1);
        exit(1);
    }

    int32_t current_number = 0;
    int32_t total_sum = 0;
    bool is_negative = false;
    bool in_number = false;

    while (bytes = read(0, buf, sizeof(buf))) {
        if (bytes == -1){
            char msg[] = "error reading from stdin\n";
            write(2, msg, sizeof(msg) - 1);
            exit(1);
        }

        for (uint32_t i = 0; i < bytes; ++i){
            if (isdigit(buf[i])) {
                current_number = current_number * 10 + (buf[i] - '0');
                in_number = true;
                continue;
            }

            switch (buf[i]) {
                case '-':
                    if (!in_number) {
                        is_negative = true;
                        in_number = true;
                    }
                    break;

                case ' ':
                case '\n':
                    if (in_number) {
                        if (is_negative) {
                            total_sum -= current_number;
                        } else {
                            total_sum += current_number;
                        }
                        current_number = 0;
                        in_number = false;
                        is_negative = false;
                    }

                    if (buf[i] == '\n') {
                        write(file, "\n", 1);
                        write_num(file, total_sum);
                        
                        write(1, "success\n", 8);
                        total_sum = 0;
                        break;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    if (bytes == -1) {
        char msg[] = "error reading from stdin\n";
        write(2, msg, sizeof(msg) - 1);
        exit(1);
    }

    close(file);
    return 0;

}