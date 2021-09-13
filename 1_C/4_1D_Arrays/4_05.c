#include<stdio.h>


int main() {
    double table[10];
    int j = 0, x = 1;
    for (int i = 0; i < 5; i++) {
        printf("Podaj %d i %d liczbe\n", j, x);
        if (scanf(" %lf %lf", &table[j], &table[x]) != 2) {
            printf("Input data type error\n");
            return 1;
        }
        j = j + 2;
        x = x + 2;
    }
    for (int a = 0; a <= 9; a++) {
        printf("Tablica[%d] = %lf\n", a, table[a]);
    }

}
