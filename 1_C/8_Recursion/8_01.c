#include<stdio.h>

unsigned long factorial_rec(int n) {

    if (n < 0) {
        return 0;
    } else if (n < 2) {
        return 1;
    } else {
        return n * factorial_rec(n - 1);
    }
}


int main() {
    int n;
    unsigned long wynik;
    printf("Podaj n: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (n < 0 || n > 20) {
        printf("Incorrect input data");
        return 2;
    }

    wynik = factorial_rec(n);


    printf("Wynik: %ld", wynik);
    return 0;

}