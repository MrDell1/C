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

long long binary_exponentiation(long long a, unsigned int n) {
    if (n % 2 != 0) {
        return a * power_rec(power_rec(a, 2), ((n - 1) / 2));
    } else {
        return power_rec(power_rec(a, 2), (n / 2));
    }
}


int main() {
    int a, n;
    long long wynik;
    printf("Podaj podstawe: ");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }


    printf("Podaj wykladnik: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        return 1;
    }


    wynik = binary_exponentiation(a, n);


    printf("Wynik: %lld", wynik);
    return 0;

}
