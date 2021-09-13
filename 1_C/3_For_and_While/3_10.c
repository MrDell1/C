#include<stdio.h>


int main() {
    float a, b = 0;
    for (int i = 0; i < 10; i++) {
        printf("Podaj %d liczbe ", i + 1);
        if (scanf("\t %f", &a) != 1) {
            printf("Incorrect input");
            return 1;
        }

        b = b + a;

    }
    printf("%f", b);


}
