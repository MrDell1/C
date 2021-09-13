#include<stdio.h>

int main() {
    int tab[11][11], x = 0;


    for (int i = 0; i < 11; i++) {
        for (x = 0; x < 11; x++) {
            tab[x][i] = x * i;
            printf(" %d ", tab[x][i]);
        }
        printf("\n");
    }
}

