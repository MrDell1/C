#include<stdio.h>


int sum_of_digits(long long number) {
    if (number == 0)
        return 0;
    if (number < 0) {
        number *= -1;
    }
    return (number % 10 + sum_of_digits(number / 10));
}


int main() {
    long long a;
    long long wynik;
    printf("Podaj podstawe: ");
    if (scanf("%lld", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }

    if (a < 0) {
        a *= -1;
    }


    wynik = sum_of_digits(a);


    printf("Wynik: %lld", wynik);
    return 0;

}