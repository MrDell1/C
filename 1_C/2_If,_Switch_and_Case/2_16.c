#include<stdio.h>


int main() {

    int a;
    printf("Podaj liczbe calkowita:  \n");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input ");
        return 1;
    }
    if (a > 0) {
        printf("dodatnia");
    } else if (a < 0) {
        printf("ujemna");
    } else {
        printf("zerowa");
    }


}