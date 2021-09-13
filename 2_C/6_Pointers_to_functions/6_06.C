#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comparators_06.h"

func_array *funcs;

int main() {
       funcs = (func_array*)malloc(sizeof(func_array) * 4);
    if(funcs == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    *(funcs + 0) = comp_int;
    *(funcs + 1) = comp_int_abs;
    *(funcs + 2) = comp_int_length;
    *(funcs + 3) = comp_int_digits_sum;


    int x = 0;
    printf("Podaj długość tablicy:");
    if(scanf("%d", &x) != 1){
        printf("Incorrect input");
        free(funcs);
        return 1;
    }
    if(x <= 0){
        printf("Incorrect input data");
        free(funcs);
        return 2;
    }
    int *tab = (int*)malloc(sizeof(int) * x);
    if(tab == NULL){
        printf("Failed to allocate memory");
        free(funcs);
        return 8;
    }
    printf("Podaj liczby:");
    for(int i = 0; i < x; i++){
        if(scanf("%d",(tab + i)) != 1){
            printf("Incorrect input");
            free(tab);
            free(funcs);
            return 1;
        }
    }
    int op = 0;
    printf("Podaj rodzaj operacji:");
    if(scanf("%d", &op) != 1){
        printf("Incorrect input");
        free(tab);
        free(funcs);
        return 1;
    }
    if(op < 0 || op > 3){
        printf("Incorrect input data");
        free(tab);
        free(funcs);
        return 2;
    }
    int res;
    switch(op){
        case 0:{
             res = sort_int(tab, x, (*(funcs + 0)));

            break;
        }
        case 1:{
            res = sort_int(tab, x, (*(funcs + 1)));
            break;
        }
        case 2:{
            res = sort_int(tab, x, (*(funcs + 2)));
            break;
        }
        case 3:{
            res = sort_int(tab, x, (*(funcs + 3)));
            break;
        }
        default:{
            printf("Incorrect input data");
            free(tab);
            free(funcs);
            return 2;
        }
    }
    if(res == 1){
        printf("Failed to allocate memory");
        free(tab);
        free(funcs);
        return 8;
    }
    for(int i = 0; i < x; i++) {
        printf("%d ", *(tab + i));
    }
    free(tab);
    free(funcs);
    return 0;
}