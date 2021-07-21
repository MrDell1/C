#include <stdio.h>
#include "int_operations_02.h"


int main() {


    int x = 0, a , b;
    printf("Enter numbers: ");
    if(scanf("%d %d", &a, &b) != 2){
        printf("Incorrect input");
        return 1;
    }
    printf("Choose an operation: ");
    if(scanf("%d", &x) != 1){
        printf("Incorrect input");
        return 1;
    }
    switch(x){
        case 0:{
            printf("%d", get_function (op_add)(a, b));
            break;
        }
        case 1:{
            printf("%d", get_function (op_sub)(a, b));
            break;
        }
        case 2:{
            printf("%d", get_function (op_div)(a, b));
            break;
        }
        case 3:{
            printf("%d", get_function (op_mul)(a, b));
            break;
        }
        default:{
            printf("Incorrect input data");
            return 2;
        }
    }

    return 0;
}