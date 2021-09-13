#include<stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {


    char tab[102] = "\0";


    int sum = 0, i = 0;
    int g = 0;
    printf("Podaj wyrazenie: \n");
    fgets(tab, 101, stdin);
    for (int k = 0; k < 102; k++) {
        if (tab[k] < 48 || tab[k] > 57) {
            if (tab[k] != '+' && tab[k] != '-' && tab[k] != '\n' && tab[k] != '\0') {
                printf("Incorrect input");
                return 1;
            }

        }
    }

    while (tab[i] != '\0') {

        if (tab[i] >= 48 && tab[i] <= 57) {
            if (tab[i + 1] >= 48 && tab[i + 1] <= 57) {
                int j = i + 1;
                char ciag[10] = "\0";
                while (tab[j] >= 48 && tab[j] <= 57) {

                    j++;
                }
                g = 0;
                g = j - i;
                strncat(ciag, &tab[i], g);
                if (tab[i - 1] == '+') {
                    sum = sum + atoi(ciag);
                    i = i + g;
                } else if (tab[i - 1] == '-') {
                    sum = sum - atoi(ciag);
                    i = i + g;
                } else {
                    sum = atoi(ciag);
                    i = i + g;
                }
                memset(ciag, 0, sizeof(ciag));
            } else if (tab[i - 1] == '+') {
                sum = sum + (tab[i] - 48);
                i++;
            } else if (tab[i - 1] == '-') {
                sum = sum - (tab[i] - 48);
                i++;
            } else {
                sum = (tab[i] - 48);
                i++;
            }

        }

        i++;
    }
    printf("%d", sum);
}
