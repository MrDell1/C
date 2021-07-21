#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char tab[31];
    printf("Podaj sciezke do plik:\n");
    if (fgets(tab, 31, stdin)) {
        char *p;
        if (p = strchr(tab, '\n')) {
            *p = 0;
        } else {
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }
    FILE *file = fopen(tab, "r");
    if (file == NULL) {
        printf("Couldn't open file");
        return 4;
    }

    int k = fgetc(file);
    while (k != EOF) {

        if (k != 9 && k != 13 && k != 32 && k != 10 && k!= 45) {
            if (k > 57 || k < 48) {
                printf("File corrupted");
                fclose(file);
                return 6;
            }
        }
        k = fgetc(file);
    }

    fseek(file, 0,0);
    int num = 0, sum = 0;
    fscanf(file, "%d", &sum);
    while (!feof (file)) {
        num = 0;
        fscanf(file, "%d", &num);
        sum += num;
    }
    printf("Suma wczytanych liczb wynosi: %d", sum);

    fclose(file);
    return 0;
}
