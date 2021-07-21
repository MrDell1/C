#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "big_numbers.h"

int create(struct big_numbers_t *bn, int capacity){
    if(bn == NULL || capacity <= 0){
        return 1;
    }
    bn->big_number = (char**)calloc(capacity, sizeof(char*));
    if(bn->big_number == NULL){
        return 2;
    }
    for(int i = 0; i < capacity; i++){
        *(bn->big_number + i) = NULL;
    }
    bn->capacity = capacity;
    bn->size = 0;
    return 0;
}
int create_big_numbers(struct big_numbers_t **bn, int capacity){
    if(bn == NULL || capacity <= 0){
        return 1;
    }
    *bn = (struct big_numbers_t *)malloc(sizeof(struct big_numbers_t));
    if(*bn == NULL){
        return 2;
    }
    int err = create(*bn, capacity);
    if(err == 2){
        free(*bn);
        *bn = NULL;
        bn = NULL;
        return 2;
    }
    else if(err == 1){
        free(*bn);
        *bn = NULL;
        bn = NULL;
        return 1;
    }

    return 0;

}
void destroy(struct big_numbers_t *bn){
    if(bn != NULL && bn->size >= 0 && bn->capacity >= 0){
            for (int i = 0; i < bn->capacity; i++) {
                free(*(bn->big_number + i));
            }

        free(bn->big_number);

    }


}
void destroy_big_numbers(struct big_numbers_t **bn){
    if(*bn != NULL && (*bn)->size >= 0 && (*bn)->capacity >= 0 && (*bn)->size <= (*bn)->capacity && (*bn)->big_number != NULL){
        destroy(*bn);
        free(*bn);
        *bn = NULL;
    }

}
int add_big_number(struct big_numbers_t *bn, const char *big_number){
    if(bn == NULL || big_number == NULL || bn->size < 0 || bn->size > bn->capacity || bn->big_number == NULL){
        return 1;
    }
    if(*(big_number + 0) == 45){
        for(int i = 1; i < (int)strlen(big_number); i++){
            if(*(big_number + i) < 48 || *(big_number + i) > 57){
                return 1;
            }
        }
    }
    else{
        for(int i = 0; i < (int)strlen(big_number); i++){
            if(*(big_number + i) < 48 || *(big_number + i) > 57){
                return 1;
            }
        }
    }

    if (*(big_number + 0) > 48 && *(big_number + 0) <= 57) {
        for (int i = 1; i < (int) strlen(big_number); i++) {

            if (*(big_number + i) < 48 || *(big_number + i) > 57) {
                return 1;
            }

        }
    } else if (strlen(big_number) == 1 && *(big_number + 0) == '0') {
        goto Next;
    } else if (*(big_number + 0) == '-' && (*(big_number + 1) > 48 && *(big_number + 1) <= 57)) {
        goto Next;
    } else {
        return 1;
    }
    Next:;
    if(bn->size >= bn->capacity){
        return 3;
    }

    *(bn->big_number + bn->size) = (char*)calloc(strlen(big_number) + 1, 1);
    if(*(bn->big_number + bn->size) == NULL){
        return 2;
    }
    strcpy(*(bn->big_number + bn->size), big_number);
    bn->size++;

    return 0;
}
void display(const struct big_numbers_t *bn){
    if(bn != NULL && bn->size >= 0 && bn->capacity >= 0 && bn->size <= bn->capacity && bn->big_number != NULL){

        for(int i = 0; i < bn->size; i++){
            printf("%s\n", *(bn->big_number + i));
        }

    }
}