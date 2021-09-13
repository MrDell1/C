#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comparators_08.h"



int main() {
    int (*funcs[])(const void*, const void*) = {&comp_int, &comp_double, &comp_point};

    int type = 0;
    printf("Enter data type:");
    if(scanf("%d", &type) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(type < 0 || type > 2){
        printf("Incorrect input data");
        return 2;
    }

    int x = 0;
    printf("Podaj długość tablicy:");
    if(scanf("%d", &x) != 1){
        printf("Incorrect input");
        return 1;
    }
    if(x <= 0){
        printf("Incorrect input data");
        return 2;
    }

    switch(type){
        case 0:{
            int *tab = (int*)malloc(sizeof(int) * x);
            if(tab == NULL){
                printf("Failed to allocate memory");
                return 8;
            }
            printf("Podaj liczby:");
            for(int i = 0; i < x; i++){
                if(scanf("%d",(tab + i)) != 1){
                    printf("Incorrect input");
                    free(tab);
                    return 1;
                }
            }
            int res = sort(tab, x, sizeof(*(tab)),(*(funcs + 0)));
            if(res == 1){
                printf("Failed to allocate memory");
                free(tab);
                return 8;
            }
            for(int i = 0; i < x; i++) {
                printf("%d ", *(tab + i));
            }
            free(tab);
            return 0;
            break;
        }
        case 1:{
            double *tab =  (double*)malloc(sizeof(double ) * x);
            if(tab == NULL){
                printf("Failed to allocate memory");
                return 8;
            }
            printf("Podaj liczby:");
            for(int i = 0; i < x; i++){
                if(scanf("%lf",(tab + i)) != 1){
                    printf("Incorrect input");
                    free(tab);
                    return 1;
                }
            }
            int res = sort(tab, x, sizeof(*(tab)),(*(funcs + 1)));
            if(res == 1){
                printf("Failed to allocate memory");
                free(tab);
                return 8;
            }
            for(int i = 0; i < x; i++) {
                printf("%lf ", *(tab + i));
            }
            free(tab);
            return 0;
            break;
        }
        case 2:{
            struct point_t *tab= (struct point_t*)malloc(sizeof(struct point_t) * x);
            if(tab == NULL){
                printf("Failed to allocate memory");
                return 8;
            }
            printf("Podaj liczby:");
            for(int i = 0; i < x; i++){
                if(scanf("%lf %lf",&(tab + i)->x, &(tab + i)->y) != 2){
                    printf("Incorrect input");
                    free(tab);
                    return 1;
                }
            }
            int res = sort(tab, x, sizeof(*(tab)),(*(funcs + 2)));
            if(res == 1){
                printf("Failed to allocate memory");
                free(tab);
                return 8;
            }
            for(int i = 0; i < x; i++) {
                printf("%lf %lf\n",(tab + i)->x, (tab + i)->y);
            }
            free(tab);
            return 0;
            break;
        }
        default:{
            printf("Incorrect input data");
            return 2;
        }
    }

}
