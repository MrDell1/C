#include<stdio.h>


int main() {
    int macA[15][15], macB[15][15], zmien = 0, count = 0;

    printf("podaj liczbe\n");
    for (int i = 0; i < 15; i++) {
        if (scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &macA[i][0], &macA[i][1], &macA[i][2], &macA[i][3],
                  &macA[i][4], &macA[i][5], &macA[i][6], &macA[i][7], &macA[i][8], &macA[i][9], &macA[i][10],
                  &macA[i][11], &macA[i][12], &macA[i][13], &macA[i][14]) != 15) {
            printf("incorrect input\n");
            return 1;
        }

    }

    for (int k = 0; k < 15; k++) {
        for (int x = 0; x < 15; x++) {
            if (macA[k][x] >= 0 && macA[k][x] < 30) {

            } else {
                printf("value out of range\n");
                return 2;
            }
        }
    }

    for (int k = 0; k < 15; k++) {
        for (int x = 0; x < 15; x++) {
            zmien = macA[k][x];
            count = 0;
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    if (zmien == macA[i][j]) {
                        count++;
                    }
                }
            }
            macB[k][x] = count;
        }
    }

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            printf("%d ", macB[i][j]);
        }
        printf("\n");
    }

    return 0;
}

