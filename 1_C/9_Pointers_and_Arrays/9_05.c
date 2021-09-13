#include<stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    float T[20];
    float *x = T;
    srand(time(0));
    for (int i = 0; i < 20; i++) {
        *x = (float) rand() / (float) (RAND_MAX) * 5.0;

        printf("%.1f ", *x);
        x++;
    }
    printf("\n");
    float *c = T;
    for (int i = 0; i < 10; i++) {
        printf("%.1f ", *c);
        c += 2;
    }


    return 0;

}