#include<stdio.h>
#include "vector_utils_18.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int reverse_vector(int *tab, int size) {
    if (tab == NULL || size <= 0) {
        return 1;
    }
    int *tab2 = (tab + size - 1);
    while (tab < tab2) {
        swap(tab, tab2);
        tab++;
        tab2--;
    }
    return 0;
}

int find_min(const int *tab, int size, int *min) {
    if (tab == NULL || size <= 0 || min == NULL) {
        return 1;
    }
    *min = *tab;
    tab++;
    for (int i = 1; i < size; i++) {
        if (*min > *tab) {
            *min = *tab;
        }
        tab++;
    }

    return 0;
}


int main() {
    int T[100];
    int *x = T;
    int min = 0;
    int *m = &min;

    printf("Wpisuj wartosci calkowite\n");
    int size = read_vector(x, 100, -1);
    if (size == -2) {
        printf("Incorrect input");
        return 1;
    } else if (size == 0 || size == -1) {
        printf("Not enough data available");
        return 3;
    }
    find_min(x, size, m);

    printf("%d", *m);

    return 0;

}
