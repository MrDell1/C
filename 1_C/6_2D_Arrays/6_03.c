#include<stdio.h>


int main() {
    int tab[5][5];
    int i, x, a = 4, b = 4;
    printf("Wpisz macierz");
    for (x = 0; x < 5; x++) {
        if (scanf("%d %d %d %d %d", &tab[x][0], &tab[x][1], &tab[x][2], &tab[x][3], &tab[x][4]) != 5) {
            printf("incorrect input");
            return 1;
        }


    }
    for (x = 0; x < 5; x++) {
        for (i = 0; i < 5; i++) {
            if (x == i) {
                printf("%d ", tab[x][i + a]);
                a = a - 2;
                if (x == 2) {
                    b = b - 2;
                }
            } else if (i == (x + b)) {
                printf("%d ", tab[x][i - b]);
                b = b - 2;

            } else {
                printf("%d ", tab[x][i]);
            }
        }
        printf("\n");
    }

}
