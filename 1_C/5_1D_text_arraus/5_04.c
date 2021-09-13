#include<stdio.h>

int main() {
    char name[1001];
    int x = 0, i = 0;
    printf("Podaj tekst:\n");
    fgets(name, 1001, stdin);
    while (name[i] != '\0') {
        if ((name[i] >= ' ' && name[i] <= '~')) {
            x++;
        }
        i++;
    }

    printf("%d", x);

    return 0;

}

