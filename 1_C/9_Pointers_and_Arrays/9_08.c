#include<stdio.h>
#include "vector_utils_08.h"

int sort(int *tab, int size) {
    if (size <= 0 || tab == NULL) {
        return 1;
    }
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*(tab + j) > *(tab + j + 1)) {
                temp = *(tab + j);
                *(tab + j) = *(tab + j + 1);
                *(tab + j + 1) = temp;
            }
        }
    }
    return 0;
}


int main() {
    int T[100];
    int *x = T;

    printf("Wpisuj wartosci calkowite\n");
    int size = read_vector(x, 100, -1);
    if (size == -2) {
        printf("Incorrect input");
        return 1;
    } else if (size == 0 || size == -1) {
        printf("Not enough data available");
        return 3;
    }

    sort(x, size);

    display_vector(x, size);

    return 0;

}