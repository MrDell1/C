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
        if (table[a] % 2 == 0) {
            printf("%d even\n", table[a]);
        } else {
            printf("%d odd\n", table[a]);
        }
    }

}
