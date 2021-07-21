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

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Couldn't open file");
        fclose(file);
        remove("temp.txt");
        return 4;
    }


    int k = fgetc(file), x = 0;
    while (k != 10) {
        if (k != 32) {
            if (k > 57 || k < 48) {
                printf("File corrupted");
                fclose(file);
                fclose(temp_file);
                remove("temp.txt");
                return 6;
            }
        }
        x++;
        k = fgetc(file);
    }

    if(x == 0){
        printf("File corrupted");
        fclose(file);
        fclose(temp_file);
        remove("temp.txt");
        return 6;
    }
    char copy = fgetc(file);
    while(!feof(file)){
        if(copy == '\n'){
            fputc(32, temp_file);
        }
        else{
            fputc(copy, temp_file);
        }
        copy = fgetc(file);
    }



    fseek(temp_file, 0, SEEK_END);
    int end = ftell(temp_file) + x;

    fseek(file, 0,SEEK_SET);
    int num = 0, lenght= ftell(file);
    char ch;

    fclose(temp_file);

    FILE *temp_file_r = fopen("temp.txt", "r");
    if (temp_file_r == NULL) {
        printf("Couldn't open file");
        fclose(file);
        remove("temp.txt");
        return 4;

    }


    fseek(temp_file_r, 0, SEEK_SET);
    fseek(file, 0, SEEK_SET);
    k = fgetc(file);
    while(k != 10) {
        fseek(file, lenght, SEEK_SET);
        fscanf(file, "%d", &num);

        if (num > end || num < x) {
            printf("File corrupted");
            fclose(temp_file_r);
            fclose(file);
            remove("temp.txt");
            return 6;
        }
        lenght = ftell(file);
        fseek(temp_file_r, (num - x - 1), SEEK_SET);

        num = 0;
        k = fgetc(file);
        fseek(file, lenght, SEEK_SET);
    }


    fseek(temp_file_r, 0, SEEK_SET);
    fseek(file, 0, SEEK_SET);
    k = fgetc(file);
    lenght = 0;
    while(k != 10){
        fseek(file, lenght, SEEK_SET);
        fscanf(file, "%d", &num);


        lenght = ftell(file);
        fseek(temp_file_r, (num - x - 1), SEEK_SET);
        ch = fgetc(temp_file_r);


        printf("%c", ch);
        num = 0;
        k = fgetc(file);
        fseek(file, lenght, SEEK_SET);
    }

    fclose(temp_file_r);
    fclose(file);
    remove("temp.txt");

    return 0;
}
