#include<stdio.h>


int main() {
    int macA[5][5], macB[5][5], macC[5][5], sumA[5], sumB[5];

    printf("podaj liczbe\n");
    for (int i = 0; i < 5; i++) {
        if (scanf("%d %d %d %d %d", &macA[i][0], &macA[i][1], &macA[i][2], &macA[i][3], &macA[i][4]) != 5) {
            printf("incorrect input\n");
            return 1;
        }

    }
    printf("podaj liczbe\n");
    for (int i = 0; i < 5; i++) {
        if (scanf("%d %d %d %d %d", &macB[i][0], &macB[i][1], &macB[i][2], &macB[i][3], &macB[i][4]) != 5) {
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
        for (int j = 0; j < 5; j++) {
            sumB[i] = sumB[i] + macB[j][i];
        }
    }


    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (sumA[i] > sumB[i]) {
                macC[j][i] = macA[j][i];
            } else if (sumA[i] < sumB[i]) {
                macC[j][i] = macB[j][i];
            } else {
                macC[j][i] = macA[j][i];
            }

        }
    }

    for (int i = 0; i < 5; i++) {
        printf("%d %d %d %d %d\n", macC[i][0], macC[i][1], macC[i][2], macC[i][3], macC[i][4]);
    }

    return 0;
}
