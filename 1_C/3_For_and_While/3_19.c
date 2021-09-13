#include<stdio.h>

int main() {
    int a, c = 0;
    printf("Podaj liczbe: \n");
    if (scanf("%d", &a) != 1) {
        printf("Incorrect input");
        return 1;
    } else {

        for (int i = 1; i <= a; i++) {
            if ((a % i) == 0) {
                c++;
            }
        }
        if (c == 2) {
            printf("YES");
        } else {
            printf("NO");
        }


    }


}