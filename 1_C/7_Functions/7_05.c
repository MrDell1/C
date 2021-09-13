#include<stdio.h>


int add(int a, int b) {
    int sum;
    sum = a + b;
    return sum;
}

int main() {
    int a, b, sum;
    printf("Podaj pierwszą liczbę: ");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj drugą liczbę: ");
    if (scanf("%d", &b) != 1) {
        printf("Incorrect input");
        return 1;
    }

    sum = add(a, b);
    printf("Wynik: %d", sum);
    return 0;

}