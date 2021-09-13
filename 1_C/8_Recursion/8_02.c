#include<stdio.h>


long power_rec(int a, int n) {
    if (n < 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (n == 1) {
        return a;
    } else {
        int p = power_rec(a, n - 1);
        return a * p;
    }

}


int main() {
    int a, n;
    unsigned long wynik;
    printf("Podaj a: ");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }
    printf("\n");
    printf("Podaj n: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (n < 0) {
        printf("Incorrect input data");
        return 2;
    }

    wynik = power_rec(a, n);


    printf("Wynik: %ld", wynik);
    return 0;

}
