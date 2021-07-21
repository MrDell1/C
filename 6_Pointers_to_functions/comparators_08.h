//
// Created by Marcin on 24.05.2021.
//

#ifndef DANTE_COMPARATORS_H
#define DANTE_COMPARATORS_H

struct point_t
{
    double x;
    double y;
};

typedef int  (*func_array)(const void *a, const void *b);
int sort(void *array, int len, int size, int(*funcs)(const void *, const void *));

int comp_int(const void *a, const void *b);
int comp_double(const void *a, const void *b);
int comp_point(const void *a,const void *b);


#endif //DANTE_COMPARATORS_H