#include<stdio.h>


int main() {
    int table[10];
    int j = 0, x = 1;
    for (int i = 0; i < 5; i++) {
        printf("Podaj %d i %d liczbe\n", j, x);
        if (scanf(" %d %d", &table[j], &table[x]) != 2) {
            printf("Input data type error\n");
            return 1;
        }
        j = j + 2;
        x = x + 2;
    }
    for (int a = 0; a <= 9; a++) {
        if (table[a] > 1) {
            int b = 0;
            for (int c = 1; c <= table[a]; c++) {
                if (table[a] % c == 0) {
                    b++;
                }
            }
            if (b == 2) {
                printf("%d prime\n", table[a]);
            } else {
                printf("%d composite \n", table[a]);
            }
        } else {
            printf("%d other\n", table[a]);
        }
    }

}