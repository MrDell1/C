#include<stdio.h>


int is_prime(int a) {
    int count = 0;
    for (int i = a; i > 0; i--) {
        if ((a % i) == 0) {
            count++;
        }
    }
    if (count == 2) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int a, b, tab[100];
    printf("Podaj x1: ");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj x2: ");
    if (scanf("%d", &b) != 1) {
        printf("Incorrect input");
        return 1;
    }

    if (a > b) {
        printf("Incorrect input");
        return 1;
    }

    int g = 0;
    for (int i = a; i <= b; i++) {
        if (is_prime(i) == 1) {
            tab[g] = i;
            g++;
        }
    }

    if (g == 0) {
        printf("nothing to show");
        return 0;
    }

    for (int c = 0; c < g; c++) {
        printf("%d ", tab[c]);
    }


    return 0;

}
