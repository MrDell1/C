#include<stdio.h>



int main() {
    float a;
    float b;
    float c;
    printf("Wpisz liczbe calkowita a\n");
    scanf("%f", &a);
    printf("Wpisz liczbe calkowita b\n");
    scanf("%f", &b);

    c = a + b ;
    printf("%f\n", c);
    c = a - b;
    printf("%f\n", c);
    c = a * b;
    printf("%f\n", c);
    c = a/b;
    printf("%f\n", c);

}