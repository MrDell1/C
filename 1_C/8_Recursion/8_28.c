#include<stdio.h>

unsigned long power_rec(unsigned long a, int n) {
    if (n < 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (n == 1) {
        return a;
    } else {
        unsigned long p = power_rec(a, n - 1);
        return a * p;
    }

}

unsigned long loga(unsigned long b, unsigned long n) {
    if (b > n) {
        return 0;
    } else {
        return 1 + loga(b, n / b);
    }
}

unsigned long reverse_number(unsigned long a) {

    unsigned long digit = loga(10, a);


    if (a == 0)
        return 0;

    return ((a % 10 * power_rec(10, digit)) + reverse_number(a / 10));
}


int main() {
    unsigned long a = 0, b = 0;
    unsigned long wynik;
    printf("podaj x1: ");
    if (scanf("%lu", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }
    printf("podaj x1: ");
    if (scanf("%lu", &b) != 1) {
        printf("Incorrect input");
        return 1;
    }


    a = reverse_number(a);
    b = reverse_number(b);

    wynik = a + b;

    printf("%lu", reverse_number(wynik));

    return 0;

}