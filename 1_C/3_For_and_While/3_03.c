#include<stdio.h>

int main() {

    double a, b;

    printf("Podaj kwote:  \n");
    if (scanf("%lf", &a) != 1) {
        printf("Incorrect input ");
        return 1;
    } else if (a < 0) {
        printf("Incorrect input ");
        return 1;
    }
    printf("Podaj czas:  \n");
    if (scanf("%lf", &b) != 1) {
        printf("Incorrect input ");
        return 1;
    } else if (b < 0) {
        printf("Incorrect input ");
        return 1;
    }

    for (int i = 0; i < b; i++) {
        a = a * 1.01;
    }
    printf("%.2lf", a);

}


