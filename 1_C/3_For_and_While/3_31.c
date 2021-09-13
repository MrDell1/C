#include<stdio.h>
#include <math.h>

#define eps pow(10, -4)

int main() {
    double a = 0, n = 1, b = 0.000000;

    do {
        a = 1 / (n * (n + 1));
        b = b + a;
        n++;
    } while (a >= eps);
    printf("Liczba wyrazow i suma: %.0f, %.4f", n - 2, b - 0.0001);
}
