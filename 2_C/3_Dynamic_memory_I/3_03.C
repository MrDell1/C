#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float* create_array(int N);


int main() {
    int n = 0;
    printf("Podaj rozmiar tablicy");
    if(scanf("%d", &n) != 1){
        printf("Incorrect input");
        return 1;
    }
    else if(n <= 0){
        printf("Incorrect input data");
        return 2;
    }
    float *tab = create_array(n);
    if(tab == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < n; i++){
        if(scanf("%f", (tab+i)) != 1){
            free (tab);
            printf("Incorrect input");
            return 1;
        }
    }
    for(int i = n - 1; i >= 0; i--){
        printf("%f ", *(tab + i));
    }
    free (tab);
    return 0;
}

float* create_array(int N){
    if(N <= 0){
        return NULL;
    }
    float *tab;
    tab = (float*)malloc(sizeof *tab * N);
    if(!tab){

        return NULL;
    }

    return tab;

}