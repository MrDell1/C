#include<stdio.h>


int main() {
    float table[10], min, max;
    float b = 0;
    int j = 0, x = 1;
    for (int i = 0; i < 5; i++) {
        printf("Podaj %d i %d liczbe\n", j, x);
        if (scanf(" %f %f", &table[j], &table[x]) != 2) {
            printf("Input data type error\n");
            return 1;
        }
        j = j + 2;
        x = x + 2;
    }
    for (int a = 0; a <= 9; a++) {
        b = b + table[a];
    }
    printf("%.4f\n", b / 10);

    max = table[0];
    for (int g = 1; g <= 9; g++) {
        if (max < table[g]) {
            max = table[g];
        }
    }
    printf("%.0f\n", max);

    min = table[0];
    for (int c = 1; c <= 9; c++) {
        if (min > table[c]) {
            min = table[c];
        }
    }
    printf("%.0f\n", min);

}
