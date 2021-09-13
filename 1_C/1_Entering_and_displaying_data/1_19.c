#include<stdio.h>
#include <math.h>



int main() {
    float a;
    float b;

    printf("Podaj liczbe:  \n");
    scanf("%f", &a);

    b=2*powf( a, 3) - 4*powf(a,2) + 3*a - 7;
    printf("%f", b);
}