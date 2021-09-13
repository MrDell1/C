#include<stdio.h>

int main() {
    char name[30];

    printf("Wpisz swoje imie\n");
    scanf("%30s", name);
    for (int i = 0; i < 30; i++) {
        if (name[i] >= 'a' && name[i] <= 'z' || name[i] >= 'A' && name[i] <= 'Z') {

        } else if (name[i] == '\0') {
            i = 30;
        } else {
            printf("Incorrect input");
            return 1;
        }
    }
    printf("Witaj %s!", name);

    return 0;

}
