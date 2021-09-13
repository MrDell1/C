#include<stdio.h>


int is_prime_rec(int n, int i) {
    if (i == 1) {
        return 1;
    } else if (i <= 0) {
        return 0;
    } else {
        if (n % i == 0) {
            return 0;
        } else {
            return is_prime_rec(n, i - 1);
        }
    }
}


int is_superprime_rec(int number) {

    int prime = is_prime_rec(number, number / 2);
    if (prime == 1) {
        if (number / 10 != 0) {
            return is_superprime_rec(number / 10);
        } else {
            return 1;
        }

    } else {
        return 0;
    }


}


int main() {
    int a;
    long long wynik;
    printf("Podaj podstawe: ");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input");
        return 1;
    }


    wynik = is_superprime_rec(a);
    if (wynik == 0) {
        printf("NO");
    } else {
        printf("YES");
    }


    //printf("Wynik: %lld", wynik);
    return 0;

}

