#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
    char tab_s[31], tab_o[31];

    printf("Podaj sciezke do pliku: \n");

    if (fgets(tab_s, 31, stdin)) {
        char *p;
        if (p = strchr(tab_s, '\n')) {
            *p = 0;
        } else {
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }

    if (*tab_s == -52) {
        printf("Couldn't open file\n");
        return 4;
    }
    FILE *s_file = fopen(tab_s, "r");

    if (s_file == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }

    printf("Podaj sciezke do pliku wyjściowego:");

    if (fgets(tab_o, 31, stdin)) {
        char *p_o;
        if (p_o = strchr(tab_o, '\n')) {//check exist newline
            *p_o = 0;
        } else {
            scanf("%*[^\n]");
            scanf("%*c");//clear upto newline
        }
    }



    if (*tab_o == -52) {
        fclose(s_file);
        printf("Couldn't create file");
        return 5;
    }
    FILE *o_file = fopen(tab_o, "w");
    if (o_file == NULL) {
        fclose(s_file);
        printf("Couldn't create file");
        return 5;
    }


    fseek(s_file, 0, SEEK_END);
    int s_lenght = ftell(s_file);

    for(int i = s_lenght-1; i >= 0; i--){
            fseek(s_file, i, SEEK_SET);
            fputc(fgetc(s_file), o_file);
    }




    fclose(s_file);
    fclose(o_file);

    printf("File copied");


    return 0;
}
