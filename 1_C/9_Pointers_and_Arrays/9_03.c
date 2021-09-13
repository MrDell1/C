#include<stdio.h>


int main() {
    int T[10];
    int *x = T;

    for (int i = 0; i < 10; i++) {
        *x = i;

        printf("%d ", *x);
        x++;
    }


    return 0;

}