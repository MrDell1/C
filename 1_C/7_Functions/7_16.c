#include<stdio.h>
#include <math.h>

int factorial(int x) {
    int fact = 1;
    if (x == 0 || x == 1) {
        return 1;
    } else {
        for (int i = 1; i <= x; i++) {
            fact *= i;
        }
        return fact;
    }
}

double mySin(double x, int n) {
    double sumsin = 0;
    if (n < 0) {
        sumsin = -1;
        return sumsin;
    } else {
        for (int i = 0; i <= n; i++) {
            sumsin = sumsin + (((pow(-1, i)) / (factorial((2 * i + 1)))) * pow(x, (2 * i + 1)));
        }
        return sumsin;
    }

}

double myCos(double x, int n) {
    double sumcos = 0;
    if (n < 0) {
        sumcos = -1;
        return sumcos;
    } else {
        for (int i = 0; i <= n; i++) {
            sumcos = sumcos + (((pow(-1, i)) / (factorial((2 * i)))) * pow(x, (2 * i)));
        }
        return sumcos;
    }
}

int main() {
    double cos, sumsin, sumcos;
    int tay;
    printf("Podaj wartosc kata, dla ktorego chcesz obliczyc wartosc funkcji sin i cos: ");
    if (scanf("%lf", &cos) != 1) {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj liczbę wyrazów szegegu Taylora: ");
    printf("\n");
    if (scanf("%d", &tay) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (tay < 0) {
        printf("Incorrect input");
        return 1;
    }

    sumsin = mySin(cos, tay);
    sumcos = myCos(cos, tay);

    printf("%lf %lf", sumsin, sumcos);
    return 0;

}

