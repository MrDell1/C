#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141593

int main() {
    float *tab;
    tab = (float*)malloc(sizeof *tab);
    if(!tab){
        printf("Failed to allocate memory");
        return 8;
    }

        *(tab) = PI;


        printf("%f %p", *tab,(void*)&tab);

    free (tab);
    return 0;
}