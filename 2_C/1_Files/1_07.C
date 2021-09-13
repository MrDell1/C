#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int n = 0, zarodek;
    time_t tt;
    zarodek = time(&tt);
    srand(zarodek);
    printf("Podaj liczbe liczb:\n");
    if(scanf("%d", &n) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(n < 1 || n > 1000){
        printf("Incorrect input data");
        return 2;
    }

    int j=0;
    char name[10];
    while (n > 0){
        sprintf(name,"%d.txt",j);

        FILE *file = fopen(name, "w");
        if(file == NULL){
            printf("couldn't create file");
            return 5;
        }
        printf("%s\n", name);
        if(n < 10) {
            for (int i = 0; i < n; i++) {
                fprintf(file, "%d\n", rand() % 1001);
            }
        }
        else{
            for (int i = 0; i < 10; i++) {
                fprintf(file, "%d\n", rand() % 1001);
            }
        }

        j++;
        n -= 10;

        fclose(file);
    }



    return 0;
}
