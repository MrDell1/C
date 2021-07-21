#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


int *count_words(const char *filename, int *err_code, int N, ...) {
    if (filename == NULL || N <= 0) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return NULL;
    }
    if (err_code != NULL) {
        *err_code = 0;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        if (err_code != NULL) {
            *err_code = 2;
        }
        return NULL;
    }
    int *tab = NULL;
    if (tab == NULL) {
        tab = (int*)malloc(sizeof(int) * N);
        if (tab == NULL) {
            if (err_code != NULL) {
                *err_code = 3;
            }
            fclose(file);
            return NULL;
        }

    }

    va_list vaList, vaList1;


    int j = 0;
    for (int i = 0; i < N; i++) {
        *(tab + j) = 0;
        int ch;
        ch = fgetc(file);
        while (ch != EOF) {
                    va_start(vaList1, N);
            for (int c = i; c > 0; c--) {
                        va_arg(vaList1, char*);
            }

            if (ch == *(va_arg(vaList1, char*) + 0)) {
                        va_start(vaList, N);
                for (int c = i; c > 0; c--) {
                            va_arg(vaList, char*);
                }
                int str_len = (int) strlen(va_arg(vaList, char*));
                        va_end(vaList);
                if (str_len > 1) {
                    int k = 1;
                            va_start(vaList, N);
                    for (int c = i; c > 0; c--) {
                                va_arg(vaList, char*);
                    }
                    ch = fgetc(file);
                    while (ch == *(va_arg(vaList, char*) + k)) {
                        ch = fgetc(file);
                        k++;
                                va_end(vaList);
                                va_start(vaList, N);
                        for (int c = i; c > 0; c--) {
                                    va_arg(vaList, char*);
                        }

                    }
                            va_end(vaList);
                    if (k == str_len) {
                        int cur_pos = ftell(file);
                        int err = 0;
                        fseek(file, cur_pos - 1, SEEK_SET);
                        ch = fgetc(file);

                        if((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)){
                            fseek(file, cur_pos, SEEK_SET);
                            err = 1;
                            goto End;
                        }
                        if(cur_pos - 1 - (str_len + 1) < 0){
                            err = 0;
                            goto End;
                        }
                        fseek(file, cur_pos - 1 - (str_len + 1), SEEK_SET);
                        ch = fgetc(file);
                        if(ch != 2 && ch != '\n') {
                            if ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
                                fseek(file, cur_pos, SEEK_SET);
                                err = 1;
                                goto End;
                            }
                        }
                        else {
                            fseek(file, cur_pos, SEEK_SET);
                            err = 0;
                            goto End;
                        }
                        End:;
                        if (err == 0) {
                            fseek(file, cur_pos, SEEK_SET);
                            *(tab + j) += 1;
                        }
                    }

                } else {
                    int cur_pos = ftell(file);
                    int err = 0;
                    fseek(file, cur_pos, SEEK_SET);
                    ch = fgetc(file);

                    if((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)){
                        fseek(file, cur_pos, SEEK_SET);
                        err = 1;
                        goto Endv2;
                    }
                    if(cur_pos - (str_len + 1) < 0){
                        err = 0;
                        goto Endv2;
                    }
                    fseek(file, cur_pos - (str_len + 1), SEEK_SET);
                    ch = fgetc(file);
                    if(ch != 2 && ch != '\n') {
                        if ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
                            fseek(file, cur_pos, SEEK_SET);
                            err = 1;
                            goto Endv2;
                        }
                    }
                    else {
                        fseek(file, cur_pos, SEEK_SET);
                        err = 0;
                        goto Endv2;
                    }
                    Endv2:;
                    if (err == 0) {
                        fseek(file, cur_pos, SEEK_SET);
                        *(tab + j) += 1;
                    }
                }


            }
                    va_end(vaList1);
            ch = fgetc(file);
        }
        fseek(file, 0, SEEK_SET);
        j++;

    }
    if (err_code != NULL) {
        *err_code = 0;
    }
    fclose(file);
            va_end(vaList);
            va_end(vaList1);
    return tab;
}

int main(int argc, char **argv) {
    if(argc > 2){
    if (strcmp(*(argv + 1), "0") == 0) {
        if (argc <= 2) {
            printf("Not enough arguments");
            return 9;
        }
    }
    else{
        if (argc <= 2) {
            printf("Not enough arguments");
            return 9;
        }
    }
    }
    else{
        printf("Not enough arguments");
        return 9;
    }
    int err_code;
    char *name;


    if (strcmp(*(argv + 1), "0") == 0) {
        name = (char*)malloc((int) (strlen(*(argv + 2))) + 1);
        if (name == NULL) {

            printf("Failed to allocate memory");
            return 8;
        }
        strcpy(name, *(argv + 2));
    } else {
        name = (char*)malloc((int) (strlen(*(argv + 1))) + 1);
        if (name == NULL) {

            printf("Failed to allocate memory");
            return 8;
        }
        strcpy(name, *(argv + 1));
    }


    int *counts;
    if (strcmp(*(argv + 1), "0") == 0) {
        for (int i = 3; i < argc; i++) {
            counts = count_words(name, &err_code, 1, *(argv + i));
            if (err_code > 0) {
                if (err_code <= 2) {
                    printf("Couldn't open file");

                    free(name);
                    return 4;
                } else {

                    free(name);
                    printf("Failed to allocate memory");
                    return 8;
                }
            }
            printf("%d\n", *counts);
            free(counts);
        }
    } else {
        for (int i = 2; i < argc; i++) {
            counts = count_words(name, &err_code, 1, *(argv + i ));
            if (err_code > 0) {
                if (err_code <= 2) {
                    printf("Couldn't open file");
                    free(name);
                    return 4;
                } else {
                    free(name);
                    printf("Failed to allocate memory");
                    return 8;

                }

            }
            if (counts != NULL) {
                printf("%d\n", *counts);
                free(counts);
            }
        }
    }

    free(name);

    return 0;


}