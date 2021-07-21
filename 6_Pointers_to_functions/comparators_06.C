#include <string.h>
#include <stdlib.h>
#include "comparators_06.h"

int sort_int(int *array, int len, int(*funcs)(int, int)) {
    if (array == NULL || funcs == NULL || len <= 0) {
        return 1;
    }
    int x = len, temp;
    for (int i = 0; i < x; i++) {
        for (int j = i + 1; j < x; j++) {
            if (funcs(*(array + i), *(array + j)) > 0) {
                temp = *(array + i);
                *(array + i) = *(array + j);
                *(array + j) = temp;
            }
        }
    }

        return 0;
}

int comp_int(int a, int b) {
    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    } else {
        return 0;
    }
}

int comp_int_abs(int a, int b) {
    if (abs(a) < abs(b)) {
        return -1;
    } else if (abs(a) > abs(b)) {
        return 1;
    } else {
        return 0;
    }
}

int comp_int_length(int a, int b) {
    int a_len = 0, b_len = 0;
    do {
        a_len++;
        a /= 10;
    } while (a != 0);
    do {
        b_len++;
        b /= 10;
    } while (b != 0);

    if (a_len < b_len) {
        return -1;
    } else if (a_len > b_len) {
        return 1;
    } else {
        return 0;
    }
}

int comp_int_digits_sum(int a, int b) {
    if(a < 0){
        a *= -1;
    }
    if(b < 0){
        b *= -1;
    }

    int temp_a = a, temp_b = b, x, sum_a = 0, sum_b = 0;

    while (temp_a != 0) {
        x = temp_a % 10;
        sum_a += x;
        temp_a /= 10;
    }

    while (temp_b != 0) {
        x = temp_b % 10;
        sum_b += x;
        temp_b /= 10;
    }

    if (sum_a < sum_b) {
        return -1;
    } else if (sum_a > sum_b) {
        return 1;
    } else {
        return 0;
    }
}

