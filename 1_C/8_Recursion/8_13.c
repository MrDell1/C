#include<stdio.h>

int getRemainder(int num, int divisor) {
    return (num - divisor * (num / divisor));
}

int sum_of_digits(long long number) {
    if (number == 0) {
        return 0;
    }
    if (number < 0) {
        number *= -1;
    }
    return (number % 10 + sum_of_digits(number / 10));
}

int is_divisible_by_3(int number) {

    int sum = sum_of_digits(number);
    int remainder = getRemainder(sum, 3);
    if (remainder == 0) {
        return 1;
    } else {
        return 0;
    }
}


int main() {
    int a;
    long long wynik;
    printf("Podaj podstawe: ");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }


    wynik = is_divisible_by_3(a);
    if (wynik == 0) {
        printf("NO");
    } else {
        printf("YES");
    }


    //printf("Wynik: %lld", wynik);
    return 0;

}
