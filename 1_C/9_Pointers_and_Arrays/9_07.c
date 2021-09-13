#include<stdio.h>

int sum(const float *tab, unsigned int size, float *result) {
    if (size <= 0 || tab == NULL || result == NULL) {
        return 1;
    }
    *result = 0;
    for (unsigned int i = 0; i < size; i++) {
        *result += *tab;
        tab++;
    }
    return 0;

}

int avg(const float *tab, unsigned int size, float *result) {
    if (size <= 0 || tab == NULL || result == NULL) {
        return 1;
    }
    *result = 0;
    sum(tab, size, result);
    *result = *result / size;

    return 0;
}

int read_vector_float(float *tab, int size, float stop_value) {
    if (size <= 0 || tab == NULL) {
        return -1;
    }
    int licznik = 0;
    for (int i = 0; i < size; i++) {
        if (scanf("%f", tab + i) != 1) {
            return -2;
        }
        if (*(tab + i) == stop_value) {
            break;
        }
        licznik++;
    }
    return licznik;
}


int main() {
    float T[100], sum_f = 0, avg_f = 0;
    float *x = T, *sum_p = &sum_f, *avg_p = &avg_f;

    printf("Wpisuj wartosci calkowite\n");
    int size = read_vector_float(x, 100, 0);
    if (size == -2) {
        printf("Incorrect input");
        return 1;
    } else if (size == 0 || size == -1) {
        printf("Not enough data available");
        return 3;
    }

    sum(x, size, sum_p);

    avg(x, size, avg_p);
    printf("Suma: %.2f\nSrednia: %.2f", *sum_p, *avg_p);


    return 0;

}