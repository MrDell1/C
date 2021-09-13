#include<stdio.h>



int main() {
    int a;
    int b;
    int c;
    printf("Wpisz liczbe calkowita a\n");
    scanf("%d", &a);
    printf("Wpisz liczbe calkowita b\n");
    scanf("%d", &b);

    c = a + b ;
    printf("%d\n", c);
    c = a - b;
    printf("%d\n", c);
    c = a * b;
    printf("%d\n", c);
    c = a/b;
    printf("%d\n", c);

}