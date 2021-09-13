#include<stdio.h>
#include <string.h>

void reverse(char *begin, char *end) {
    char temp;
    while (begin < end) {
        temp = *begin;
        *begin++ = *end;
        *end-- = temp;
    }
}

void reverseWords(char *s) {
    char *word_begin = s;

    // Word boundary
    char *temp = s;

    // Reversing individual words
    while (*temp) {
        temp++;
        if (*temp == '\0') {
            reverse(word_begin, temp - 1);
        } else if (*temp == ' ') {
            reverse(word_begin, temp - 1);
            word_begin = temp + 1;
        }
    }

    // Reverse the entire string
    reverse(s, temp - 1);
}

int main() {


    char tab[1001] = {'\0'}, longest[1001] = {'\0'};
    int j = 0, i = 0, index[1000] = {0}, h = 0;
    int count = 0, max = 0;

    printf("Podaj tekst: \n");
    fgets(tab, 1001, stdin);
    int lenght = strlen(tab);
    for (int k = 0; k < lenght; k++) {
        if (tab[k] < 65 || tab[k] > 90) {
            if ((tab[k] < 97 || tab[k] > 122) && (tab[k] != 32 && tab[k] != '\0' && tab[k] != '\n')) {
                printf("Incorrect input");
                return 1;
            }

        }
    }

    for (i = 0; i < lenght; i++) {
        if (tab[i] != ' ') {

            count++;

        } else {
            if (count >= max) {
                if (count > max) {
                    max = count;
                    h = 0;
                    for (int g = 0; g < 1000; g++) {
                        index[g] = 0;
                    }
                    index[h] = i - max;
                    h++;
                } else {
                    index[h] = i - max;
                    h++;
                }

            }
            count = 0;
        }
    }
    if (tab[i - 1] == '\n') {
        count--;
    }

    if (count > max) {
        max = count;
        h = 0;
        for (int g = 0; g < 1000; g++) {
            index[g] = 0;
        }
        if (tab[i - 1] == '\n') {
            index[h] = lenght - (max + 1);
        } else {
            index[h] = lenght - max;
        }
        h++;


    } else if (count == max) {

        max = count;
        if (tab[i - 1] == '\n') {
            index[h] = lenght - (max + 1);
        } else {
            index[h] = lenght - max;
        }
        h++;
    }


    for (int g = 0; g < h; g++) {

        for (i = index[g]; i < index[g] + max; i++) {
            if (tab[i] != '\n') {
                longest[j] = tab[i];
                j++;
            }
        }
        if (h > 1) {
            longest[j] = ' ';
            j++;
        }
    }
    longest[j] = '\0';
    printf("%d ", h);
    if (tab[i - 1] == '\n' && i == 1000) {
        printf(" %d\n", max - 1);
    } else {
        printf(" %d\n", max);
    }


    char *temp = longest;
    reverseWords(longest);


    for (int c = 0; c < j; c++) {
        if (temp[c] == ' ') {
            printf("\n");
        } else {

            printf("%c", temp[c]);
        }
    }


    return 0;
}