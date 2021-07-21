#include <stdio.h>
#include "int_operations_02.h"

fun get_function (enum operations_t x){
    int (*funcs[])() = {add_int, sub_int, div_int, mul_int};
    switch(x){
        case op_add:{
            return *(funcs);
        }
        case op_sub:{
            return *(funcs + 1);
        }
        case op_div:{
            return *(funcs + 2);
        }
        case op_mul:{
            return *(funcs + 3);
        }
        default: {
            return NULL;
        }
    }
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