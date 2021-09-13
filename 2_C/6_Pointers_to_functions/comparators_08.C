#include <string.h>
#include <stdlib.h>
#include "comparators_08.h"


int sort(void *array, int len, int size, int(*funcs)(const void *, const void *)) {
    if (array == NULL || funcs == NULL || len <= 0 || size <= 0) {
        return 1;
    }
    int x = len;

    if(size == 4) {
        int temp;
        for (int i = 0; i < x; i++) {
            for (int j = i + 1; j < x; j++) {
                if (funcs((((int *)array) + i), (((int *)array) + j)) > 0) {
                    temp = *(((int *)array) + i);
                    *(((int *)array) + i) = *(((int *)array) + j);
                    *(((int *)array) + j) = temp;
                }
            }
        }
    }
    else if(size == 8){
        double temp;
        for (int i = 0; i < x; i++) {
            for (int j = i + 1; j < x; j++) {
                if (funcs((((double *)array) + i), (((double *)array) + j)) > 0) {
                    temp = *(((double *)array) + i);
                    *(((double *)array) + i) = *(((double *)array) + j);
                    *(((double *)array) + j) = temp;
                }
            }
        }
    }
    else if(size == sizeof(struct point_t)){
        struct point_t temp;
        for (int i = 0; i < x; i++) {
            for (int j = i + 1; j < x; j++) {
                if (funcs((((struct point_t*)array) + i), (((struct point_t*)array) + j)) > 0) {
                    temp = *(((struct point_t*)array) + i);
                    *(((struct point_t*)array) + i) = *(((struct point_t*)array) + j);
                    *(((struct point_t*)array) + j) = temp;
                }
            }
        }
    }
    else{

        char* ptr = (char *) array;
        char *temp = (char*)malloc(size);
        for (int i = 0; i < x; i++) {
            for (int j = i + 1; j < x; j++) {
                if (funcs(ptr + i*size, ptr + j*size ) > 0) {
                    memcpy(temp, ptr + i*size, size);
                    memcpy(ptr + i*size, ptr + j*size, size);
                    memcpy(ptr + j*size, temp, size);
                }
            }
        }
        free(temp);
    }

    return 0;
}


int comp_int(const void *a, const void *b) {
    if (a == NULL || b == NULL) {
        return 2;
    } else {
        if (*(int*)a < *(int*)b) {
            return -1;
        } else if (*(int*)a > *(int*)b) {
            return 1;
        } else {
            return 0;
        }
    }
}

int comp_double(const void *a, const void *b) {
    if (a == NULL || b == NULL) {
        return 2;
    } else {
        if (*(double*)a < *(double*)b) {
            return -1;
        } else if (*(double*)a > *(double*)b) {
            return 1;
        } else {
            return 0;
        }
    }
}

int comp_point(const void *ptr1, const void *ptr2) {
    if (ptr1 == NULL || ptr2 == NULL) {
        return 2;
    } else {
        struct point_t *a;
        struct point_t *b;
        a = (struct point_t*)ptr1;
        b = (struct point_t*)ptr2;

        if (a->x > b->x) {
            return 1;
        } else if (a->x == b->x){
            if(a->y == b->y){
                return 0;
            }
            else if(a->y > b->y){
                return 1;
            }
        }

    }
    return -1;

}
