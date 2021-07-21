#include <stdio.h>
#include <stdlib.h>
#include "array_07.h"

int array_create(struct array_t *a, int N) {
    if (a == NULL || N <= 0) {
        return 1;
    }

    a->ptr = (int*)malloc(sizeof(int) * N);

    if (!a->ptr) {
        return 2;
    }
    a->size = 0;
    a->capacity = N;


    return 0;

}

int array_push_back(struct array_t *a, int value) {
    if (a == NULL || a->ptr == NULL || a->size < 0 || a->capacity <= 0 || a->size > a->capacity) {
        return 1;
    }
    if (a->capacity == 1) {
        *(a->ptr + a->size) = value;
        a->size++;
        return 0;
    } else if (a->size == a->capacity) {
        return 2;
    } else {
        *(a->ptr + a->size) = value;
        a->size++;
        return 0;
    }
}

int array_separate(const struct array_t *a, struct array_t *odd, struct array_t *even) {
    if (a == NULL || odd == NULL || even == NULL || a->ptr == NULL || a->size < 0 || a->size > a->capacity || a==odd || a == even || odd == even ) {
        return -1;
    }

    int pos = 0, neg = 0;

    for (int i = 0; i < a->capacity; i++) {
        if (*(a->ptr + i) % 2 == 0) {
            pos++;
        } else {
            neg++;
        }
    }
    if(pos > 0 && neg > 0){
        if(array_create(even, pos) > 0){
            return 0;
        }
        if(array_create(odd, neg) > 0){
            array_destroy(even);
            return 0;
        }
        int temp_pos = 0, temp_neg = 0;
        for (int i = 0; i < a->capacity; i++) {
            if (*(a->ptr + i) % 2 == 0) {
                *(even->ptr+temp_pos) = *(a->ptr + i);
                temp_pos++;
            } else {
                *(odd->ptr+temp_neg) = *(a->ptr + i);
                temp_neg++;
            }
        }
        even->size = temp_pos;
        odd->size = temp_neg;
    }
    else if(neg == 0){
        if(array_copy(a, even) > 0){
            return 0;
        }
        return 2;
    }
    else{
        if(array_copy(a, odd) > 0){
            array_destroy(even);
            return 0;
        }
        return 1;
    }

    return 3;
}

int array_copy(const struct array_t *src, struct array_t *dest) {
    if(src == NULL || dest == NULL || src->ptr == NULL || src->size < 0 || src->size > src->capacity || src == dest){
        return 1;
    }
    if(array_create(dest, src->size) > 0 ){
        return 2;
    }
    else{

        int i;
        for( i = 0; i < src->size; i++){
            *(dest->ptr+i) = *(src->ptr + i);
        }
        dest->size = i;
        dest->capacity = src->capacity;
    }
    return 0;
}

void array_display(const struct array_t *a) {
    if (a == NULL || a->ptr == NULL || a->size <= 0 || a->size > a->capacity) {

    } else {
        for (int i = 0; i < a->size; i++) {
            printf("%d ", *(a->ptr + i));
        }
        printf("\n");
    }

}

void array_destroy(struct array_t *a) {
    if (a == NULL) {

    } else {
        free(a->ptr);

    }
}