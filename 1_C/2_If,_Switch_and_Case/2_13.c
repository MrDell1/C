#include<stdio.h>


int main() {


    double T[5], min, max, average;


    printf("Podaj liczbe zmienno przecinkowa:  \n");
    scanf("%lf %lf %lf %lf %lf", &T[0], &T[1], &T[2], &T[3], &T[4]);


    min = max = T[0];
    if (T[1] < min) {
        min = T[1];
    }
    if (T[2] < min) {
        min = T[2];
    }
    if (T[3] < min) {
        min = T[3];
    }
    if (T[4] < min) {
        min = T[4];
    }

    if (T[1] > max) {
        max = T[1];
    }
    if (T[2] > max) {
        max = T[2];
    }
    if (T[3] > max) {
        max = T[3];
    }
    if (T[4] > max) {
        max = T[4];
    }
    average = (T[0] + T[1] + T[2] + T[3] + T[4]) / 5;
    printf("%.2lf\n", min);
    printf("%.2lf\n", max);
    printf("%.2lf\n", average);
}
