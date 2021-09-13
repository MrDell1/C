#include<stdio.h>


int main() {

    int count = 0;
    char tab[10] = {0};

    printf("Podaj imie: \n");
    scanf("%s", tab);

    for (int i = 0; i < 10; i++) {
        if (tab[i] == '\0') {
            count++;
        }
    }


    if (tab[9 - count] == 'a') {
        printf("Imie zenskie");
    } else {
        printf("Imie meskie");
    }

}