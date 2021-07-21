#include <stdio.h>
#include <stdlib.h>

int create_array_2d_2(int ***ptr,int width, int height);
void destroy_array_2d(int ***ptr, int height);
void display_array_2d(int **ptr, int width, int height);
int sum_array_2d(int **ptr, int width, int height);
int sum_row(int *ptr, int width);

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
    int **matrix;
    if(create_array_2d_2(&matrix,w, h) > 0){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int x;
            if(scanf("%d", &x) != 1){
                printf("Incorrect input");
                destroy_array_2d(&matrix, h);
                return 1;
            }
            *(*(matrix + i) + j) = x;
        }
    }
    display_array_2d(matrix, w, h);

    for(int i = 0; i < h; i++){
        int x = sum_row(*(matrix + i), w);
        if(x != -1) {
            printf("%d\n", x);
        }
    }

    int x = sum_array_2d(matrix, w, h);
    if(x != -1){
        printf("%d\n", x);
    }



    destroy_array_2d(&matrix, h);
    return 0;
}

int create_array_2d_2(int ***ptr,int width, int height){

    if(ptr == NULL || width <= 0 || height <= 0){
        return 1;
    }

    *ptr = (int**)malloc(height * 2 * sizeof(int));
    if(*ptr == NULL){
        //printf("Failed to allocate memory");
        *ptr = NULL;
        return 2;
    }
    for(int r = 0; r < height; r++){
        *(*ptr + r) = (int*)malloc(width * sizeof(int));
        if(*(*ptr + r) == NULL){
            for(int c = r - 1;c >= 0; c--){
                free(*(*ptr + c));
            }
            free(*ptr);
            *ptr = NULL;
            //printf("Failed to allocate memory");
            return 2;
        }
    }
    return 0;
}

int sum_row(int *ptr, int width){
    if(ptr == NULL || width <= 0){
        return -1;
    }
    int count = 0;
    for(int i = 0; i < width; i++){
        count += *(ptr + i);
    }
    return  count;
}

int sum_array_2d(int **ptr, int width, int height){
    if(ptr == NULL || width <= 0 || height <= 0){
        return -1;
    }
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
             count += *(*(ptr + i) + j);
        }

    }
    return count;
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

void destroy_array_2d(int ***ptr, int height){
    if(ptr == NULL || height <= 0){

    }
    else{
        for(int i = 0; i < height; i++){
            free(*(*ptr + i));
        }
        free(*ptr);
        *ptr = NULL;
    }
}