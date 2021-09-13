#include<stdio.h>


int main() {
    int macA[5][5], sumA = 0, sumB = 0;

    printf("podaj liczbe\n");
    for (int i = 0; i < 5; i++) {
        if (scanf("%d %d %d %d %d", &macA[i][0], &macA[i][1], &macA[i][2], &macA[i][3], &macA[i][4]) != 5) {
            printf("incorrect input\n");
            return 1;
        }

    }
    for (int i = 0; i < 5; i++) {
        sumA = sumA + macA[i][i];
    }
    int x = 4;
    for (int i = 0; i < 5; i++) {
        sumB = sumB + macA[i][x];
        x--;
    }

    printf("%d %d", sumA, sumB);


    return 0;
}
