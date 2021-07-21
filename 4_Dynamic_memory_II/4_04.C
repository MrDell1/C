#include <stdio.h>
#include <stdlib.h>
struct matrix_t{
    int **ptr;
    int width;
    int height;
};

int matrix_create(struct matrix_t *m, int width, int height);
int matrix_read(struct matrix_t *m);
void matrix_display(const struct matrix_t *m);
void matrix_destroy(struct matrix_t *m);



int main() {
    int h, w;
    struct matrix_t m;
    printf("Podaj szerokosc i wysokosc: ");
    if(scanf("%d %d", &w, &h) != 2){
        printf("Incorrect input");
        return 1;
    }
    if(h <= 0 || w <= 0){
        printf("Incorrect input data");
        return 2;
    }

    if(matrix_create(&m, w, h) > 0){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    if(matrix_read(&m) != 0){
        printf("Incorrect input");
        return 1;
    }
    matrix_display(&m);
    matrix_destroy(&m);
    return 0;
}

int matrix_create(struct matrix_t *m, int width, int height){
    if(m == NULL || width <= 0 || height <= 0){
        return 1;
    }

    m->ptr = (int**)malloc(height * 2 * sizeof(int));
    if(m->ptr == NULL){
        //printf("Failed to allocate memory");

        return 2;
    }
    for(int r = 0; r < height; r++){
        *(m->ptr + r) = (int*)malloc(width * sizeof(int));
        if(*(m->ptr + r) == NULL){
            for(int c = r - 1;c >= 0; c--){
                free(*(m->ptr + c));
            }
            free(m->ptr);

            //printf("Failed to allocate memory");
            return 2;
        }
    }
    m->height = height;
    m->width = width;
    return 0;
}

int matrix_read(struct matrix_t *m){
    if(m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0){
        return 1;
    }

    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            int x;
            if(scanf("%d", &x) != 1){
                matrix_destroy(m);
                return 2;
            }
            *(*(m->ptr + i) + j) = x;
        }
    }


    return 0;
}

void matrix_display(const struct matrix_t *m){
    if(m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0){

    }
    else {
        for (int i = 0; i < m->height; i++) {
            for (int j = 0; j < m->width; j++) {
                printf("%d ", *(*(m->ptr + i) + j));
            }
            printf("\n");
        }
    }
}

void matrix_destroy(struct matrix_t *m){
    if(m == NULL || m->ptr == NULL || m->height <= 0){

    }
    else{
        for(int i = 0; i < m->height; i++){
            free(*(m->ptr + i));
        }
        free(m->ptr);

    }
}