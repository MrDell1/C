#include<stdio.h>
#include <math.h>

int main() {

    double a;
    double wynik;
    printf("Podaj liczbe:  \n");
    if (scanf("%lf", &a) != 1) {
        printf("Incorrect input ");
        return 1;
    }
    if (a > 5) {

        wynik = ((a / 2) - 2) * (2 - (0.75 * a));
        printf("%lf", wynik);
    } else if (a < -5) {
        wynik = (pow(a, 2) + (10 * a) + 25) - 10;
        printf("%lf", wynik);
    } else {
        wynik = (2 * pow(a, 2)) + 3 * a - 1;
        printf("%lf", wynik);
    }


}

