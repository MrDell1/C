#include<stdio.h>

long int fibonacci(int n) {
    if (n < 0) {
        return -1;
    } else if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 2) + fibonacci(n - 1);
    }

}


int main() {
    int n;
    unsigned long wynik;

    printf("Który wyraz ciagu fibonacciego chcesz wyznaczyć: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (n < 0) {
        printf("Incorrect input data");
        return 2;
    }

    wynik = fibonacci(n);


    printf("Wynik: %lu", wynik);
    return 0;

}
