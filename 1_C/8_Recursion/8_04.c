#include<stdio.h>


unsigned long sum_rec(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return (n + sum_rec(n - 1));
    }

}


int main() {
    int n;
    unsigned long wynik;

    printf("Podaj liczbę, dla której chcesz policzyć sumę: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (n <= 0) {
        printf("Incorrect input data");
        return 2;
    }

    wynik = sum_rec(n);


    printf("Wynik: %lu", wynik);
    return 0;

}