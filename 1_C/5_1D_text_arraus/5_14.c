#include<stdio.h>
#include <string.h>


int main() {


    char tab[1001] = {'\0'};
    int i;
    int count = 0;

    printf("Podaj tekst: \n");
    fgets(tab, 1001, stdin);
    int lenght = strlen(tab);


    for (i = 0; i < lenght; i++) {
        if (i == 0) {
            if (tab[i] > 64 && tab[i] < 91) {

            } else if (tab[i] > 96 && tab[i] < 123) {

            } else {
                count--;
            }
        }
        if (tab[i] > 64 && tab[i] < 91) {

        } else if (tab[i] > 96 && tab[i] < 123) {

        } else {
            if (tab[i + 1] > 64 && tab[i + 1] < 91) {
                count++;
            } else if (tab[i + 1] > 96 && tab[i + 1] < 123) {
                count++;
            } else if (tab[i] == '\n' || tab[i] == '\0') {
                count++;
            }
        }


    }
    if (lenght == 1000) {
        count++;
    }
    printf("%d", count);


    return 0;
}