#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void write_file_ignore_arabic(FILE *file_input, FILE *file_output){
    int c;
    
    while (( c = getc(file_input)) != EOF){
        if (isdigit(c))
            continue;
        
        fputc(c, file_output);
    }
}

void write_amount_latin(FILE *file_input, FILE *file_output){
    int c;
    int count = 0;

    while ((c = fgetc(file_input)) != EOF){
        if (c == '\n'){
            fprintf(file_output, "%d\n", count);
            count = 0;
            continue;
        }

        if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')
            ++count;
    }

    if (count > 0)
        fprintf(file_output, "%d", count);
}

void write_amount_non_latin_arabic_space(FILE *file_input, FILE *file_output){
    int c;
    int count = 0;

    while ((c = fgetc(file_input)) != EOF){
        if (c == '\n'){
            fprintf(file_output, "%d\n", count);
            count = 0;
            continue;
        }

        if (!(c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z') && 
        !( c >= '0' && c <= '9') && c != ' ')
            ++count;
    }

    if (count > 0)
        fprintf(file_output, "%d", count);
}

void fputc_hex(FILE *file_output, int c){
    if (c > 15){
        fputc_hex(file_output, c / 16);
    }

    int digit = c % 16;

    if (digit < 10)
        fprintf(file_output, "%d", digit);
    else
        fprintf(file_output, "%c", 'A' + digit - 10);
}

void write_non_num_hex(FILE *file_input, FILE *file_output){
    int c;
    int num;

    while ((c = fgetc(file_input)) != EOF){
        if (c == '\n'){
            fputc('\n', file_output);
            continue;
        }

        if ( c >= '0' && c <= '9'){
            fprintf(file_output, "%d ", c);
        } else{
            fputc_hex(file_output, c);
            fputc(' ', file_output);
        }
    }
}

int main(int argc, char *argv[]){
    if (argc < 3 || argc > 4){
        printf("input error\n");
        
        return 1;
    }

    char choice;
    FILE *file_input = fopen(argv[2], "r");

    if (file_input == NULL){
        printf("error opening file_input\n");
        return 1;
    }

    FILE *file_output;

    if (argv[1][1] == 'n'){
        if (argc != 4){
            printf("input error\n");
            return 1;
        }

        choice = argv[1][2];
        file_output = fopen(argv[3], "w");
    }
    else{
        if (argc != 3){
            printf("input error\n");
            return 1;
        }
        
        choice = argv[1][1];
        char file_output_name[strlen(argv[2] + strlen("_out" + 1))] = argv[2] + "_out" + '\0';
        file_output = fopen(file_output_name, "w");
    }

    if (file_output == NULL){
        printf("error opening file_output\n");
        return 1;
    }

    switch(choice){
        case 'd':
            write_file_ignore_arabic(file_input, file_output);
            break;
        case 'i':
            write_amount_latin(file_input, file_output);
            break;
        case 's':
            write_amount_non_latin_arabic_space(file_input, file_output);
            break;
        case 'a':
            write_non_num_hex(file_input, file_output);
            break;
        default:
            printf("flag error\n");
            return 1;
    }
    
    fclose(file_input);
    fclose(file_output);
}