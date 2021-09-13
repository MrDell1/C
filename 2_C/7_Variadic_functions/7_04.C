#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


char *concatenate(int num, ...) {
    if (num <= 0) {
        return NULL;
    }

    va_list vaList;
            va_start(vaList, num);

    int out_size = 0;
    int n = num;
    for (int i = 0; i < n; i++) {
        out_size += (int) strlen(va_arg(vaList, char*));
    }

    char *buf = malloc(out_size + n);
    if (buf == NULL) {
        return NULL;
    }
            va_end(vaList);
            va_start(vaList, num);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            strcpy(buf, va_arg(vaList, char*));
        } else {
            strcat(buf, va_arg(vaList, char*));
        }
        if( i + 1 == n){
            strcat(buf, "\0");
        }else {
            strcat(buf, " ");
        }
    }

            va_end(vaList);
    return buf;
}

int main(void) {

    char **tab;
    tab = malloc(4 * sizeof(char*));
    if (tab == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    for (int i = 0; i < 4; i++) {
        *(tab + i) = malloc(1001);

        if (*(tab + i) == NULL) {
            for (int j = i; j >= 0; j--) {
                free(*(tab + j));
            }
            free(tab);
            printf("Failed to allocate memory");
            return 8;
        }
    }



    int n = 0;

    printf("Enter number of elements:");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        for (int i = 0; i < 4; i++) {
            free(*(tab + i));
        }
        free(tab);
        return 1;
    }


    if (n > 4 || n < 2) {
        printf("Incorrect input data");
        for (int i = 0; i < 4; i++) {
            free(*(tab + i));
        }
        free(tab);
        return 2;
    }

    char *msg = NULL;
    printf("Podaj liczby:");
    if (n == 2) {
        for (int i = 0; i < n; i++) {
            int x;
            do {
                x = getchar();
            } while (x != '\n' && x != EOF);
            scanf("%1000[^\n]s", *(tab + i));
        }


         msg = concatenate(n, *(tab + 0), *(tab + 1));

    } else if (n == 3) {
        for (int i = 0; i < n; i++) {
            int x;
            do {
                x = getchar();
            } while (x != '\n' && x != EOF);
            scanf("%1000[^\n]s", *(tab + i));
        }


         msg = concatenate(n, *(tab + 0), *(tab + 1), *(tab + 2));

    } else if (n == 4) {
        for (int i = 0; i < n; i++) {
            int x;
            do {
                x = getchar();
            } while (x != '\n' && x != EOF);
            scanf("%1000[^\n]s", *(tab + i));
        }


         msg = concatenate(n, *(tab + 0), *(tab + 1), *(tab + 2), *(tab + 3));

    }

    if(msg == NULL){
        printf("Failed to allocate memory");
        for (int i = 0; i < 4; i++) {
            free(*(tab + i));
        }
        free(tab);
        return 8;
    }

    printf("%s", msg);
    free(msg);
    for (int i = 0; i < 4; i++) {
        free(*(tab + i));
    }
    free(tab);

    return 0;
}

