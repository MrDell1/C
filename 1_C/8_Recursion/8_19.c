#include<stdio.h>


unsigned long long decimal_to_octal(unsigned int number) {
    if (number == 0) {
        return 0;
    }
    return number % 8 + 10 * decimal_to_octal(number / 8);
}


int main() {
    int a;
    unsigned long long wynik;
    printf("podaj x1: ");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }


    wynik = decimal_to_octal(a);

    printf("%lld", wynik);

    return 0;

}

