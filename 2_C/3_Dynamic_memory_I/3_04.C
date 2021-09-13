#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int create_array_int(int **ptr, int N);
void destroy_array_int(int **ptr);


int main() {
    int n = 0;
    int tab;
    int *tab_p = &tab;

    printf("Podaj rozmiar tablicy");
    if(scanf("%d", &n) != 1){
        printf("Incorrect input");
        return 1;
    }
    else if(n <= 0){
        printf("Incorrect input data");
        return 2;
    }
    int x = create_array_int(&tab_p,n);
    if(x > 0){
        if(x == 1){
            printf("Incorrect input data");
            return 2;
        }
        else{
            printf("Failed to allocate memory");
            return 8;
        }
    }

    printf("Podaj liczby: ");
    for(int i = 0; i < n; i++){
        if(scanf("%d", (tab_p+i)) != 1){
            destroy_array_int(&tab_p);
            printf("Incorrect input");
            return 1;
        }
    }
    for(int i = n - 1; i >= 0; i--){
        printf("%d ", *(tab_p + i));
    }

    destroy_array_int((&tab_p));

    return 0;
}

int create_array_int(int **ptr, int N){
    if(ptr == NULL || N <= 0){
        return 1;
    }

    *ptr = (int*)malloc(sizeof **ptr * N);

    if(!*ptr){
        return 2;
    }


    return 0;

}
void destroy_array_int(int **ptr){
    if(ptr == NULL){

    }
    else {
        free(*ptr);
        *ptr = NULL;
    }
}