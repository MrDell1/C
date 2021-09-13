#include<stdio.h>
#include <math.h>

#define PI 3.14159265
int main() {
    float celc;
    float kel;
    float far;


    printf("Podaj temp w Celcjuszach:  \n");
    scanf("%f", &celc);

    kel = celc + 273.15;
    far = (1.8 * celc) + 32;

    printf("Temp w kelwinach: %f\n", kel);
    printf("Temp w Fahreheitach: %f\n", far);
}

