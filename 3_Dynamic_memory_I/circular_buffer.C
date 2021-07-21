#include <stdlib.h>
#include <stdio.h>
#include "circular_buffer.h"


int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if (a == NULL || N <= 0) {
        return 1;
    }
    a->ptr = (int*)malloc(N * sizeof(int));
    if (a->ptr == NULL) {
        return 2;
    }
    for (int i = 0; i < N; i++) {
        *(a->ptr + i) = 0;
    }
    a->begin = 0;
    a->end = 0;
    a->capacity = N;
    a->full = 0;
    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {
    if (cb == NULL || N <= 0) {
        return 1;
    }

    *cb = (struct circular_buffer_t *) malloc(sizeof(struct circular_buffer_t));
    if (*cb == NULL) {
        return 2;
    }
    if (circular_buffer_create(*cb, N) != 0) {
        free(*cb);
        return 2;
    }

    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a) {
    if (a != NULL) {
        if (a->ptr != NULL) {
            free(a->ptr);
        }
    }

}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    if (a != NULL) {
        circular_buffer_destroy(*a);
        free(*a);
    }
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if (cb == NULL || cb->begin < 0 || cb->end < 0 || cb->ptr == NULL || cb->capacity <= 0 ||
        cb->begin > cb->capacity || cb->end > cb->capacity) {
        return 1;
    }

    if (cb->full == 1) {
        if(cb->begin + 1 == cb->capacity){
            cb->begin = 0;
        }
        else {
            cb->begin++;
        }

    }
    *(cb->ptr + cb->end) = value;
    cb->end++;

    if (cb->end == cb->capacity) {
        cb->end = 0;
    }
    if (cb->end == cb->begin) {
        cb->full = 1;
    }

    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    if (a == NULL || a->begin < 0 || a->end < 0 || a->ptr == NULL || a->capacity <= 0 || a->begin > a->capacity ||
        a->end > a->capacity) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return 1;
    }
    int x = 0;

    if (err_code != NULL) {
        *err_code = 0;

    }
    if (err_code != NULL) {
        int count = 0;
        for (int i = 0; i < a->capacity; i++) {

            if (*(a->ptr + i) == 0) {
                count++;

            }
        }
        if (count == a->capacity) {
            *err_code = 2;
            return x;
        }
    }


    x = *(a->ptr + a->begin);
    *(a->ptr + a->begin) = 0;
    a->begin++;

    if (a->begin == a->capacity) {
        a->begin = 0;
        a->full = 0;

    } else {
        a->full = 0;

    }

    return x;


}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    if (a == NULL || a->begin < 0 || a->end < 0 || a->ptr == NULL || a->capacity <= 0 || a->begin > a->capacity ||
        a->end > a->capacity) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return 1;
    }

    int x;
    if (err_code != NULL) {
        *err_code = 0;
    }
    if (err_code != NULL) {

        int count = 0;
        for (int i = 0; i < a->capacity; i++) {

            if (*(a->ptr + i) == 0) {
                count++;

            }
        }
        if (count == a->capacity) {
            a->begin = 0;
            *err_code = 2;
        }
    }
    if (a->full == 1) {
        a->end = a->capacity;
        a->full = 0;
    }
    if (a->end == 0) {
        x = *(a->ptr + a->capacity - 1);
        *(a->ptr +  a->capacity - 1) = 0;
        a->end = a->capacity - 1;
    } else {
        x = *(a->ptr + a->end - 1);
        *(a->ptr + a->end - 1) = 0;
        a->end--;
    }
    if (a->end == 0) {

        a->end = 0;
        a->full = 0;

    } else {
        a->full = 0;

    }

    return x;


}

int circular_buffer_empty(const struct circular_buffer_t *a) {
    if (a == NULL || a->begin < 0 || a->end < 0 || a->ptr == NULL || a->capacity <= 0 || a->begin > a->capacity ||
        a->end > a->capacity) {
        return -1;
    }

    int count = 0;
    for (int i = 0; i < a->capacity; i++) {

        if (*(a->ptr + i) == 0) {
            count++;

        }
    }
    if (count == a->capacity) {

        return 1;
    }
    return 0;

}

int circular_buffer_full(const struct circular_buffer_t *a) {
    if (a == NULL || a->begin < 0 || a->end < 0 || a->ptr == NULL || a->capacity <= 0 || a->begin > a->capacity ||
        a->end > a->capacity) {
        return -1;
    }
    if (a->full == 1) {
        return 1;
    }

    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *a) {
    if (a == NULL || a->begin < 0 || a->end < 0 || a->ptr == NULL || a->capacity <= 0 || a->begin > a->capacity ||
        a->end > a->capacity) {

    } else {
        if (circular_buffer_empty(a) == 1) {
        } else {
            if (a->begin == 0 && a->end == a->capacity - 1) {
                for (int i = 0; i < a->capacity; i++) {
                    printf("%d ", *(a->ptr + i));
                }
                printf("\n");
            } else if (a->begin < a->end) {
                for (int i = a->begin; i < a->end; i++) {
                    printf("%d ", *(a->ptr + i));
                }
                printf("\n");
            } else {
                for (int i = a->begin; i < a->capacity; i++) {
                    printf("%d ", *(a->ptr + i));
                }
                for (int i = 0; i < a->end; i++) {
                    printf("%d ", *(a->ptr + i));
                }
                printf("\n");
            }
        }


    }
}