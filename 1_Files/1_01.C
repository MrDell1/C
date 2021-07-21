#include <stdio.h>
#include <stdlib.h>

int main(){
    char tab[31], ch;
    int x=0;
    printf("Podaj sciezke do pliku");
    scanf("%30[^\n]%*c", tab);

    FILE *file = fopen(tab, "r");
    //printf("%s", tab);
    if(file == NULL){
        printf("Couldn't open file");
        return 4;
    }

    else {
        while ((ch = fgetc(file)) != EOF) {
            printf("%c", ch);
            x++;
        }
    }
    if(x == 0){
        printf("Nothing to show");
    }
    fclose(file);
    return 0;
}
