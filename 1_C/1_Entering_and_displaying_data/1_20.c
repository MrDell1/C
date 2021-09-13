#include<stdio.h>
#include <math.h>

#define PI 3.14159265
int main() {
    float a;
    float b;
    float c;
    float alpha;
    float beta;
    float gama;

    printf("Podaj przyprostokatna a:  \n");
    scanf("%f", &a);
    printf("Podaj przyprostokatna b:  \n");
    scanf("%f", &b);

    c=sqrt(powf(a,2) + powf(b, 2));
    printf("Przeciw prostokatna jest rowna %.2f:  \n", c);

    alpha = acosf((powf(b,2) + powf(c,2) - powf(a,2)) / (2*c*b)) ;

    beta = acosf((powf(a,2) + powf(c,2) - powf(b,2)) / (2*a*c)) ;

    gama = acosf((powf(a,2) + powf(b,2) - powf(c,2)) / (2*a*b)) ;


    alpha = alpha * 180.0 / PI;
    beta = beta * 180.0 / PI;
    gama = gama * 180.0 / PI;

    printf("Kat alpha jest rowny %.2f\n", alpha);
    printf("Kat beta jest rowny %.2f\n", beta);
    // printf("Kat gama jest rowny %2.f\n", gama);
}