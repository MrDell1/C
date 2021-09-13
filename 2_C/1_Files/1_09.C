#include <stdio.h>
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

    int head = 0, num = 0, x = 0, var, sum = 0;
    var = fscanf(file, "%d", &head);
    if(head <= 0 || var == 0 ){
        printf("File corrupted");
        fclose(file);
        return 6;
    }
    int head_two = head;
    while(!feof(file) && head_two > 0){

        var = fscanf(file, "%d", &num);
        if(var == 0){
            printf("File corrupted");
            fclose(file);
            return 6;
        }
        else {
            sum += num;
            x++;
            head_two--;
        }
    }
    if(head > x){
        printf("File corrupted");
        fclose(file);
        return 6;
    }
    float avg = 0;
    avg = (float)sum/(float)x;

    printf("%d\n%f\n", sum, avg);

    fseek(file,0,SEEK_SET);



    fclose(file);
    return 0;
}
