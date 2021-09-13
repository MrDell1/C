#include<stdio.h>


int main() {

    int a;
    int b;

    printf("Podaj pierwszą liczbe calkowita:  ");
    if (scanf("\t%d", &a) != 1) {
        printf("Incorrect input ");
        return 1;
    } else {
        printf("Podaj druga liczbe calkowita:  ");
        if (scanf("\t%d", &b) != 1) {
            printf("Incorrect input ");
            return 1;
        } else if (b == 0) {
            printf("Operation not permitted");
            return 1;
        }
    }
    if (a % b == 0) {
        printf("%d is divisible by %d", a, b);
    } else {
        printf("%d is not divisible by %d", a, b);
    }


}
