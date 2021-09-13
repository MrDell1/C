#include<stdio.h>


float circumference(float b) {
    float obw;
    if (b < 0) {
        obw = -1;
    } else {
        obw = 3.14159 * b;
    }

    return obw;
}

int main() {
    float r, obw;
    printf("Podaj srednice kola: ");
    if (scanf("%f", &r) != 1) {
        printf("Incorrect input");
        return 1;
    } else if (r <= 0) {
        printf("Incorrect input");
        return 1;
    }
    obw = circumference(r);
    printf("Obwod kola to: %.4f", obw);

}