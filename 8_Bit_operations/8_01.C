#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_equal(int a, int b);
int is_negative(int value);



int main() {

printf("Podaj fwie liczby:");
int a, b;
if(scanf("%d %d", &a, &b) ^ 2){
    printf("Incorrect input");
    return 1;
}

if(is_equal(a, b) ^ 0){
    printf("rowne\n");
}
else{
    printf("nierowne\n");
}

if(is_negative(a) ^ 0){
    printf("ujemna ");
}
else{
    printf("nieujemna ");
}

if(is_negative(b) ^ 0){
    printf("ujemna");
}
else{
    printf("nieujemna");
}

    return 0;



}
int is_equal(int a, int b){
    if(a ^ b){
        return 0;
    }else{
        return 1;
    }
}
int is_negative(int value){
    if(value >> 31 ^ 0){
        return 1;
    }
    else{
        return 0;
    }
}