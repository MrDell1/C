#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "char_operations.h"


int main() {
    char *str = (char*)malloc(1001);
    if(str == NULL){
        printf("Failed to allocate memory");
        return 8;
    }

    char (*funcs[])(const char) = {&lower_to_upper, &upper_to_lower, &space_to_dash, &reverse_letter};
    int x = 0;
    printf("Podaj tekst:");
    fgets(str, 1000, stdin);
    setbuf(stdin, NULL);
    printf("Choose an operation:");
    if(scanf("%d", &x) != 1){
        printf("Incorrect input");
        free(str);
        return 1;
    }
    char *res;
    switch(x){
        case 0:{
             res = letter_modifier(str,  (*(funcs + 0)));

            break;
        }
        case 1:{
             res = letter_modifier(str, *(funcs + 1));

            break;
        }
        case 2:{
            res = letter_modifier(str, *(funcs + 2));

            break;
        }
        case 3:{
            res = letter_modifier(str, *(funcs + 3));

            break;
        }
        default:{
            printf("Incorrect input data");
            free(str);
            return 2;
        }
    }
    if(res == NULL){
        printf("Failed to allocate memory");
        free(str);
        return 8;
    }
    printf("%s", res);
    free(res);
    free(str);
    return 0;
}
