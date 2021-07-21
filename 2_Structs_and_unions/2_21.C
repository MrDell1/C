#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "flights.h"


int main() {
    char tab_input[40];
    struct flight flights[100];
    struct flight f[4];

    printf("Podaj nazwę pliku:");
    fgets(tab_input, 40, stdin);
    char *p;
    if (p = strchr(tab_input, '\n')) {
        *p = 0;
    } else {
        scanf("%*[^\n]");
        scanf("%*c");
    }

    int n = load_flights(flights, 100, tab_input);
    if (n == -1 || n == -2) {
        printf("Couldn't open file");
        return 4;
    } else if (n == -3) {
        printf("File corrupted");
        return 6;
    }
    int c = 0;
    int s_p = statistics_flight(flights, n, &f[c], PASSENGER);
    if (s_p > 0) {
        c++;
    }
    int s_c = statistics_flight(flights, n, &f[c], CARGO);
    if (s_c > 0) {
        c++;
    }
    int b_p = best_flight(flights, n, &f[c], PASSENGER);
    if (b_p == 0) {
        c++;
    }
    int b_c = best_flight(flights, n, &f[c], CARGO);
    if (b_c == 0) {
        c++;
    }


    if (c > 0) {
        int err = save_flights(f, c, tab_input);
        if (err == 1 || err == 2) {
            printf("Couldn't create file");
            return 5;
        }
    }
    printf("File saved");
    return 0;
}