#include <stdio.h>
#include "int_operations_01.h""


int main() {
    int (*funcs[])(int, int) = {add_int, sub_int, div_int, mul_int};

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
            printf("%d", calculate(a, b, *(funcs + x)));
            break;
        }
        case 1:{
            printf("%d", calculate(a, b, *(funcs + x)));
            break;
        }
        case 2:{
            printf("%d", calculate(a, b, *(funcs + x)));
            break;
        }
        case 3:{
            printf("%d", calculate(a, b, *(funcs + x)));
            break;
        }
        default:{
            printf("Incorrect input data");
            return 2;
        }
    }

    return 0;
}