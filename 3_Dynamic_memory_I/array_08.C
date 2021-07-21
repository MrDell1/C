#include <stdio.h>
#include <stdlib.h>
#include "array_08.h"



int array_create_struct(struct array_t **a, int N){
    if(a == NULL || N <= 0){
        return 1;
    }
    *a = (struct array_t*)malloc(sizeof(struct array_t));
    if(*a == NULL){
        return 2;
    }
    if(array_create(*a, N) > 0){
        free(*a);
        return 2;
    }
    return 0;
}

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

int array_remove_item(struct array_t *a, int value){
    if(a == NULL || a->ptr == NULL || a->size < 0 || a->size > a->capacity || a->capacity <= 0){
        return -1;
    }
    int count = 0;
    for(int i = 0; i < a->size; i++){
        if(*(a->ptr + i) == value){
            count++;
        }
    }
    int temp_size = a->size;
    for(int i = 0; i < temp_size; i++){
        if(*(a->ptr + i) == value){
            for(int j = i; j < temp_size - 1; j++){
                *(a->ptr + j) = *(a->ptr + j + 1);
            }
            temp_size --;
            i = -1;
        }
    }
    a->size = a->size - count;
    return count;
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

void array_destroy_struct(struct array_t **a){
    if(a == NULL){

    }
    else{
        array_destroy(*a);
        free(*a);
    }
}