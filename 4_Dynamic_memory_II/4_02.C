#include <stdio.h>
#include <stdlib.h>

int **create_array_2d(int width, int height);
void display_array_2d(int **ptr, int width, int height);
void destroy_array_2d(int **ptr, int height);

int main() {
    int h, w;
    printf("Podaj szerokosc i wysokosc: ");
    if(scanf("%d %d", &w, &h) != 2){
        printf("Incorrect input");
        return 1;
    }
    if(h <= 0 || w <= 0){
        printf("Incorrect input data");
        return 2;
    }
    int **matrix = create_array_2d(w, h);
    if(matrix == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int x;
            if(scanf("%d", &x) != 1){
                printf("Incorrect input");
                destroy_array_2d(matrix, h);
                return 1;
            }
            *(*(matrix + i) + j) = x;
        }
    }



    display_array_2d(matrix, w, h);
    destroy_array_2d(matrix, h);
    return 0;
}

int **create_array_2d(int width, int height){
    if(width <= 0 || height <= 0){
        return NULL;
    }
    int **matrix;
    matrix = (int**)malloc(height * 2 * sizeof(int));
    if(matrix == NULL){
        //printf("Failed to allocate memory");
        return NULL;
    }
    for(int r = 0; r < height; r++){
        *(matrix + r) = (int*)malloc(width * sizeof(int));
        if(*(matrix + r) == NULL){
            for(int c = r - 1;c >= 0; c--){
                free(*(matrix + c));
            }
            free(matrix);
            //printf("Failed to allocate memory");
            return NULL;
        }
    }
    return matrix;
}

void display_array_2d(int **ptr, int width, int height){
    if(ptr == NULL || width <= 0 || height <= 0){

    }
    else {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                printf("%d ", *(*(ptr + i) + j));
            }
            printf("\n");
        }
    }
}

void destroy_array_2d(int **ptr, int height){
    if(ptr == NULL || height <= 0){

    }
    else{
        for(int i = 0; i < height; i++){
            free(*(ptr + i));
        }
        free(ptr);
    }
}