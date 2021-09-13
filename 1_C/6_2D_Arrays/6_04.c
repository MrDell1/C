#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


int main() {
    int tabA[4][4], tabB[4][4], tabC[4][4];
    int i, x;
    srand(time(NULL));
    for (x = 0; x < 4; x++) {
        for (i = 0; i < 4; i++) {
            tabA[x][i] = rand();
            tabB[x][i] = rand();
            if (x == i) {
                tabC[x][i] = 1;
            } else {
                tabC[x][i] = 0;
            }
        }

    }
    for (x = 0; x < 4; x++) {
        for (i = 0; i < 4; i++) {
            printf("%d ", tabA[x][i]);
        }
        printf("\n");
    }
    printf("\n");
    for (x = 0; x < 4; x++) {
        for (i = 0; i < 4; i++) {
            printf("%d ", tabB[x][i]);
        }
        printf("\n");
    }
    printf("\n");
    for (x = 0; x < 4; x++) {
        for (i = 0; i < 4; i++) {
            printf("%d ", tabC[x][i]);
        }
        printf("\n");
    }

    printf("\n");


}
