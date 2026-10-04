#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
    int pipe1[2], pipe2[2];
    
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1){
        char msg[] = "error pipe creating\n";
        write(2, msg, sizeof(msg) - 1);
        exit(1);
    }
    
    char msg[] = "enter filename\n";
    write(1, msg, sizeof(msg) - 1);
    char filename[256];
    int bytes = read(0, filename, sizeof(filename));

    if (bytes <= 0){
        char msg[] = "wrong filename input\n";
        write(2, msg, sizeof(msg) - 1);
        exit(1);
    }

    filename[bytes - 1] = '\0';
    pid_t pid = fork();

    if (pid == -1){
        char msg[] = "error creating process\n";
        write(2, msg, sizeof(msg) - 1);
        exit(1);
    } else if (pid == 0){
        close(pipe1[1]);
        close(pipe2[0]);

        dup2(pipe1[0], 0);
        close(pipe1[0]);

        dup2(pipe2[1], 1);
        close(pipe2[1]);

        char *args[] = {"child", filename, NULL};
        if (execv("./child", args) == -1){
            char msg[] = "error to exec new image";
            write(2, msg, sizeof(msg) - 1);
            exit(1);
        }
    } else{
        close(pipe1[0]);
        close(pipe2[1]);

        char buf[1024];
        ssize_t bytes;

        while (bytes = read(0, buf, sizeof(buf))){
            if (bytes == -1){
                char msg[] = "wrong ints input\n";
                write(2, msg, sizeof(msg) - 1);
                exit(1);
            } else if (buf[0] == '\n'){
                break;
            }

            write(pipe1[1], buf, bytes);
            bytes = read(pipe2[0], buf, sizeof(buf));
            write(1, buf, bytes);
        }

        close(pipe1[1]);
        close(pipe2[0]);

        wait(NULL);
    }
}