#include <stdio.h>
#include <stdlib.h>
#include "array_06.h"

int array_create(struct array_t *a, int N){
    if(a == NULL || N <= 0 ){
        return 1;
    }

    a->ptr = (int*)malloc(sizeof(int) * N);

    if(!a->ptr){
        return 2;
    }
    a->size = 0;
    a->capacity = N;


    return 0;

}

int array_push_back(struct array_t *a, int value){
    if(a == NULL || a->ptr == NULL || a->size < 0 || a->capacity <= 0 || a->size > a->capacity){
        return 1;
    }
    if(a->capacity == 1){
        *(a->ptr+a->size) = value;
        a->size ++;
        return 0;
    }
    else if(a->size == a->capacity){
        return 2;
    }
    else {
        *(a->ptr + a->size) = value;
        a->size++;
        return 0;
    }
}

void array_display(const struct array_t *a){
    if(a == NULL || a->ptr == NULL || a->size < 0 || a->size > a->capacity){

    }
    else {
        for (int i = 0; i < a->size; i++) {
            printf("%d ", *(a->ptr + i));
        }
    }
}

void array_destroy(struct array_t *a){
    if(a == NULL){

    }
    else {
        free(a->ptr);

    }
}