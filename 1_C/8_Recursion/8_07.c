#include<stdio.h>


int GCD(int a, int b) {

    if (b == 0) {
        if (a < 0) {
            a *= -1;
        }
        return a;
    }

    return GCD(b, a % b);


}


int main() {
    int a, n;
    int wynik;
    printf("Podaj a: ");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }

    printf("Podaj b: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        return 1;
    }


    wynik = GCD(a, n);


    printf("Wynik: %d", wynik);
    return 0;

}
