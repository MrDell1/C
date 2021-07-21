//
// Created by Marcin on 24.05.2021.
//

#ifndef DANTE_COMPARATORS_H
#define DANTE_COMPARATORS_H
typedef int  (*func_array)(int a, int b);
int sort_int(int *array, int len, int(*funcs)(int, int));

int comp_int(int a, int b);
int comp_int_abs(int a, int b);
int comp_int_length(int a, int b);
int comp_int_digits_sum(int a, int b);

#endif //DANTE_COMPARATORS_H