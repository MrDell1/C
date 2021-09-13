#include<stdio.h>

int main() {
    float table[100], min, max;
    float b = 0;
    int i = 0;
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
    max = table[0];
    for (int c = 1; c < i - 1; c++) {
        if (min > table[c]) {
            min = table[c];
        }
    }

    for (int g = 1; g < i - 1; g++) {
        if (max < table[g]) {
            max = table[g];
        }
    }

    for (int a = 0; a < i - 1; a++) {
        b += (float) table[a];
    }

    printf("%d\n", i - 1);
    printf("%.0f\n", min);
    printf("%.0f\n", max);
    printf("%f\n", b / (float) (i - 1));
    printf("%.0f\n", b);


}