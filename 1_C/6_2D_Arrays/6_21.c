#include<stdio.h>


int main() {
    float avgA[5] = {0}, sumA[5] = {0};
    int macA[5][5];
    // macB[5][5], macC[5][5], sumA[5], sumB[5];

    printf("podaj liczbe\n");
    for (int i = 0; i < 5; i++) {
        if (scanf("%d %d %d %d %d", &macA[i][0], &macA[i][1], &macA[i][2], &macA[i][3], &macA[i][4]) != 5) {
            printf("incorrect input\n");
            return 1;
        }

    }


    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            sumA[i] = sumA[i] + macA[j][i];
        }
    }

    for (int i = 0; i < 5; i++) {
        avgA[i] = (sumA[i] / 5);
    }


    for (int i = 0; i < 5; i++) {
        printf("%.2f ", avgA[i]);
    }

    return 0;
}