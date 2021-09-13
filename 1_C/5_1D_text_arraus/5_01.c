#include<stdio.h>

int main() {
    int tab[26], g = 65;

    for (int i = 0; i < 26; i++) {
        tab[i] = g;
        g++;
        printf("%d %c %c\n", tab[i], (char) tab[i], (char) tab[i] + 32);

    }


}