#include <stdio.h>
#include <stdlib.h>


int main() {
    int **matrix;
    matrix = (int**)malloc(10 * 2 * sizeof(int));
    if(matrix == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    for(int r = 0; r < 10; r++){
        *(matrix + r) = (int*)malloc(10 * sizeof(int));
        if(*(matrix + r) == NULL){

            for(int c = r - 1;c >= 0; c--){
                free(*(matrix + c));
            }
            free(matrix);
            printf("Failed to allocate memory");
            return 8;
        }
    }

    int i;
    int j;
    for( i = 0; i < 10; i++){
        *(*(matrix + i)) = i + 1;
    }
    for( j = 0; j < 10; j++){
        *(*matrix + j) = j + 1;
    }

    for( i = 1; i < 10; i++){
        for( j = 1; j < 10; j++){
            *(*(matrix + i) + j) = *(*(matrix + i)) * *(*matrix + j) ;
        }
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            int x = *(*(matrix + i) + j);
            if(x < 10){
                printf("  %d ", x);
            }
            else if(x < 100){
                printf(" %d ", x);
            }
            else{
                printf("%d ", x);
            }

        }
        if( i != 9) {
            printf("\n");
        }
    }

    for(int r = 0; r < 10; r++){
        free(*(matrix + r));
    }
    free(matrix);

    return 0;
}