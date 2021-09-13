#include <stdio.h>
#include <string.h>

int read_file(const char *filename);

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

    int var = read_file(tab);
    if ( var <= 0) {
        printf("Couldn't open file");
        return 4;
    }

    printf("%d", var);

    return 0;
}

int read_file(const char *filename) {
    FILE *file;
    int var;
    if(filename == NULL){
        return -1;
    }
    file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    else {
        var = 1;
        while (!feof(file)) {
            char str[30] ={0};
            fscanf(file, "%s", str);
            if(strcmp(str, "") != 0) {
                printf("%s\n", str);
            }
            int x = read_file(str);
            if(x > 0){
                var += x;
            }
        }

    }
    fclose(file);
    return var;
}
