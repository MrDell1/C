#include<stdio.h>

int even_odd(int s, int n) {
    int a;
    if (n == 0) {
        return s;
    }
    if (n < 0) {
        return 0;
    }
    a = even_odd(s, n - 1);
    if (a % 2 != 0) {

        return 3 * a + 1;
    } else {
        return a / 2;
    }
}


int main() {
    int a, n;
    int wynik;
    printf("Podaj wartosc pierwszego wyrazu: ");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }


    printf("Podaj numer wyrazu, którego wartość chcesz wyznaczyc: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        return 1;
    }

    if (n < 0) {
        printf("Incorrect input data ");
        return 2;
    }

    wynik = even_odd(a, n);


    printf("Wynik: %d", wynik);
    return 0;

}

