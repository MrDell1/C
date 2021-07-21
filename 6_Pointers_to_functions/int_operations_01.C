#include <stdio.h>
int calculate(int a, int b, int(*function)(int a, int b)){
    return function(a, b);
}

int add_int(int a, int b){
    return a + b;
}

int sub_int(int a, int b){
    return a - b;
}

int div_int(int a, int b){
    if(b == 0){
        return 0;
    }
    return a / b;
}

int mul_int(int a, int b){
    return a * b;
}