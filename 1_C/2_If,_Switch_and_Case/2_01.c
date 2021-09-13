#include<stdio.h>

int main() {
    int a;
    int b;
    int c;


    printf("Podaj dwie liczby calkowite oddzielone spacja:  ");
    if(scanf("\t%d %d", &a, &b) != 2) {
        printf("Incorrect input");
        return 1;
    }
    else{
        c = a + b;
        printf("%d", c);
        return 0;
    }

}
