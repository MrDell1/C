#include<stdio.h>
#include <string.h>


int main() {
    char b[20];
    memset(b, '0', 19);   // memset masz z biblioteki string.h
    for (int i = 0; i <= 19; i++)
        printf("%d%s\n", 1, b + 19 - i);

    // wersja print żeby się upewnić co do ilości zer.
    //printf("10^%d %d%s\n", i, 1, b+19-i);
}
