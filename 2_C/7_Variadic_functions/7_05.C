#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "functions.h"


int main(void) {

    char *tab;
    tab = malloc(1001);
    if (tab == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    char *(*func[])(const char*) = {lower_to_upper, upper_to_lower, reverse_letter, space_to_dash};
    int *choice = malloc(sizeof(int) * 4);
    if(choice == NULL){
        free(tab);
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj tekst do przeksztalcenia:");
    scanf("%1000[^\n]s", (tab));

    int n = 0;

    printf("Podaj liczbe operacj do przeprowadzenia:");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        free(choice);
        free(tab);
        return 1;
    }
    if (n > 4 || n < 2) {
        printf("Incorrect input data");
        free(choice);
        free(tab);
        return 2;
    }
    printf("Podaj wybrane operacje:");

    char **res;
    if(n == 2) {
        if(scanf("%d %d", (choice + 0), (choice + 1)) != 2){
            printf("Incorrect input");
            free(choice);
            free(tab);
            return 1;
        }
         res = text_modifier(tab, n, *(func + *((choice + 0))), (*(func + *((choice + 1)))));
    }
    else if(n == 3){
        if(scanf("%d %d %d", (choice + 0), (choice + 1), (choice + 2)) != 3){
            printf("Incorrect input");
            free(choice);
            free(tab);
            return 1;
        }
         res = text_modifier(tab, n, *(func + *((choice + 0))), *(func + *((choice + 1))), *(func + *((choice + 2))));
    }
    else {
        if(scanf("%d %d %d %d", (choice + 0), (choice + 1), (choice + 2), (choice + 3)) != 4){
            printf("Incorrect input");
            free(choice);
            free(tab);
            return 1;
        }
         res = text_modifier(tab, n, *(func + *((choice + 0))), *(func + *((choice + 1))), *(func + *((choice + 2))), *(func + *((choice + 3))));
    }
    if(res == NULL){
        free(tab);
        free(choice);
        printf("Failed to allocate memory");
        return 8;
    }

    for(int i = 0; i < n; i++) {
        printf("%s\n", *(res + i));
        free(*(res + i));
    }

    free(res);
    free(choice);
    free(tab);
    return 0;


}