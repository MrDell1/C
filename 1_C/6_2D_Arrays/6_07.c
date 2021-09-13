#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


int main() {
    int tabA[4][4], tabB[4][4], tabC[4][4];
    int i, x, s;
    srand(time(NULL));
    for (x = 0; x < 4; x++) {
        for (i = 0; i < 4; i++) {
            tabA[x][i] = rand() % 10;
            tabB[x][i] = rand() % 10;
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

    for (x = 0; x < 4; x++) {
        s = 0;
        for (i = 0; i < 4; i++) {
            s += tabA[x][i];
        }
        printf("%d ", s);
    }
    printf("\n");

    for (x = 0; x < 4; x++) {
        s = 0;
        for (i = 0; i < 4; i++) {
            s += tabA[i][x];
        }
        printf("%d ", s);
    }
    printf("\n");

    for (x = 0; x < 4; x++) {
        s = 0;
        for (i = 0; i < 4; i++) {
            s += tabB[x][i];
        }
        printf("%d ", s);
    }
    printf("\n");

    for (x = 0; x < 4; x++) {
        s = 0;
        for (i = 0; i < 4; i++) {
            s += tabB[i][x];
        }
        printf("%d ", s);
    }
    printf("\n");

    for (x = 0; x < 4; x++) {
        s = 0;
        for (i = 0; i < 4; i++) {
            s += tabC[x][i];
        }
        printf("%d ", s);
    }
    printf("\n");

    for (x = 0; x < 4; x++) {
        s = 0;
        for (i = 0; i < 4; i++) {
            s += tabC[i][x];
        }
        printf("%d ", s);
    }
    printf("\n");


}

