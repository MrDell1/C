#include<stdio.h>
#include <math.h>

#define PI 3.14159265
int main() {
    float a;
    int b;



    printf("Podaj liczbe zmiennoprzecinkowa:  \n");
    scanf("%f", &a);
    printf("Podaj dokladnosc wyswietlenia:  \n");
    scanf("%d", &b);



    printf("%.*f", b, a);

}