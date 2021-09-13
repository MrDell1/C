#include<stdio.h>


int main() {
    int table[11];
    for (int j = 0; j <= 10; j++) {
        table[j] = j;
    }
    for (int i = 0; i <= 10; i++) {
        printf("%d ", table[i]);
    }
    printf("\n");
}

