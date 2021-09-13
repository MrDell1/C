#include<stdio.h>


int main() {
    double T[100];
    int num = 0;
    double *x = T;

    printf("Ile liczb chcesz wprowadzić?: ");

    if (scanf("%d", &num) != 1) {
        printf("Incorrect input");
        return 1;
    }

    if (num > 100 || num < 1) {
        printf("Incorrect input data");
        return 2;
    }

    printf("Podaj liczby: ");

    for (int i = 0; i < num; i++) {
        if (scanf("%lf", x) != 1) {
            printf("Incorrect input");
            return 1;
        }
        x++;
    }


    x--;

    for (int i = num - 1; i >= 0; --i) {
        printf("%.6lf ", *x);
        x--;
    }

    printf("\n");
    x++;
    double sum = 0;

    for (int j = 0; j < num; j++) {

        sum += *x;
        x++;
    }
    printf("Suma: %.2lf\nSrednia: %.2lf", sum, sum / num);

    return 0;

}
