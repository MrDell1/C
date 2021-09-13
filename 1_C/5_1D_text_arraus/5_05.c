#include<stdio.h>


int main() {

    int A = 0, E = 0, I = 0, O = 0, U = 0, Y = 0, a = 0, e = 0, i = 0, o = 0, u = 0, y = 0;
    char tab[1000] = {0};

    printf("Podaj tekst: \n");
    fgets(tab, 1002, stdin);

    for (int x = 0; x < 1000; x++) {
        if (tab[x] == 'A') {
            A = 1;
        } else if (tab[x] == 'E') {
            E = 1;
        } else if (tab[x] == 'I') {
            I = 1;
        } else if (tab[x] == 'O') {
            O = 1;
        } else if (tab[x] == 'U') {
            U = 1;
        } else if (tab[x] == 'Y') {
            Y = 1;
        } else if (tab[x] == 'a') {
            a = 1;
        } else if (tab[x] == 'e') {
            e = 1;
        } else if (tab[x] == 'i') {
            i = 1;
        } else if (tab[x] == 'o') {
            o = 1;
        } else if (tab[x] == 'u') {
            u = 1;
        } else if (tab[x] == 'y') {
            y = 1;
        }

    }


    printf("Wynik: %d", A + E + I + O + U + Y + a + e + i + o + u + y);

}