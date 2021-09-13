#include<stdio.h>
#include <string.h>

int main() {
    float table[100], min, max;
    float b = 0;
    int i = 0;
    char tab_min[100], tab_max[100], tab_min_out[1000], tab_max_out[1000];
    //int j=0, x=1;
    //for( i = 0 ; i < 100; i++)
    printf("Podaj dane\n");
    do {
        if (scanf("%f ", &table[i]) != 1) {
            printf("Incorrect input\n");
            return 1;
        }
        i++;
    } while ((table[i - 1] != -1) && (i < 101));

    min = table[0];
    strcpy(tab_min_out, "");
    max = table[0];
    strcpy(tab_max_out, "");
    for (int c = 0; c < i - 1; c++) {
        if (min > table[c]) {
            min = table[c];
        }
        if (max < table[c]) {
            max = table[c];
        }
    }

    for (int a = 0; a < i - 1; a++) {
        b += (float) table[a];
    }

    for (int g = 0; g < i - 1; g++) {
        if (min == table[g]) {
            sprintf(tab_min, "%d ", g);
            strcat(tab_min_out, tab_min);
        }
        if (max == table[g]) {
            sprintf(tab_max, "%d ", g);
            strcat(tab_max_out, tab_max);
        }
    }

    printf("%d\n", i - 1);
    printf("%.0f\n", min);
    printf("%.0f\n", max);
    printf("%f\n", b / (float) (i - 1));
    printf("%.0f\n", b);
    printf("%s\n", tab_min_out);
    printf("%s\n", tab_max_out);


}
