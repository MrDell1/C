#include <stdio.h>
#include <stdlib.h>

int sum_short_int_int(const void * const in1, const void * const in2, void *out);

int main(){
    short a = 5;
    int b = 5;
    int c;
    sum_short_int_int(*a,*b,*c);
    printf("%d", c);
    return 0;
}

int sum_short_int_int(const void * const in1, const void * const in2, void *out){
    if(in1 == NULL || in2 == NULL  || out == NULL){
        return 1;
    }
    int temp;
    for(int i = 0; i < 16; i++){
        temp = 0;
        temp = in1[i] + in2[i];
        out[i] = temp;
    }
    return out;
}