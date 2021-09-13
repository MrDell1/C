#include<stdio.h>


int main() {
    int table[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("%d %d %d %d %d %d %d %d %d %d %d\n", table[0], table[1], table[2], table[3], table[4], table[5], table[6],
           table[7], table[8], table[9], table[10]);
    for (int i = 0; i <= 10; i++) {
        printf("%d\n", table[i]);
    }
}