#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main() {
    int *tab;
    tab = (int*)malloc(sizeof *tab * 101);
    if(!tab){
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < 100; i++){
        *(tab + i) = i;
    }
    for(int i = 0; i < 100; i++){
        printf("%d ", *(tab + i));
    }
    free (tab);
    return 0;
}
