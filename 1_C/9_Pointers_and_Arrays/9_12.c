#include<stdio.h>
#include "vector_utils_12.h"

int create_histogram(const float *vec, int size, int *out, int out_size) {
    if (size <= 0 || vec == NULL || out == NULL || out_size <= 0) {
        return 1;
    }
    int count;
    for (int k = 0; k < out_size - 1; k++) {
        out++;
    }
    while (out_size != 0) {
        count = 0;

        for (int j = 0; j < size; j++) {
            if (*vec >= (float) out_size - 1 && *vec < (float) out_size) {
                count++;
            }
            vec++;
        }
        for (int i = 0; i < size; i++) {
            vec--;
        }

        *out = count;
        out--;
        out_size--;
    }

    return 0;
}


int main() {
    float T[100];
    float *x = T;
    int Out[11];
    int *out = Out;

    printf("Wpisuj wartosci calkowite\n");
    int size = read_vector_float(x, 100, -1);
    if (size == -2) {
        printf("Incorrect input");
        return 1;
    } else if (size == 0 || size == -1) {
        printf("Not enough data available");
        return 3;
    }


    create_histogram(x, size, out, 11);
    display_vector(out, 11);

    return 0;

}

