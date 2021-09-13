#include<stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int T[20];
    int *x = T;
    srand(time(0));
    for (int i = 0; i < 20; i++) {
        *x = rand() % 30;

        printf("%d ", *x);
        x++;
    }
    printf("\n");
    int *c = T;
    for (int i = 0; i < 10; i++) {
        printf("%d ", *c);
        c += 2;
    }


    return 0;

}
