#include <stdio.h>
#include "array_08.h"


int main() {
    int n = 0;
    struct array_t *tab;

    printf("Podaj rozmiar tablicy");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        return 1;
    } else if (n <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    int x = array_create_struct(&tab, n);
    if (x > 0) {
        if (x == 1) {
            printf("Incorrect input data");
            return 2;
        } else {
            printf("Failed to allocate memory");
            return 8;
        }
    }
    int o = 0;

    while (1) {
        printf("Co chcesz zrobić");
        if (scanf("%d", &o) != 1) {
            printf("Incorrect input");
            array_destroy_struct(&tab);
            return 1;
        }
        int value = 0;
        switch (o) {
            case 1: {
                printf("Podaj liczby: ");
                int i;
                for (i = 0; i < n; i++) {
                    if (scanf("%d", &value) != 1) {
                        array_destroy_struct(&tab);
                        printf("Incorrect input");
                        return 1;
                    }
                    if (value == 0) {
                        break;
                    } else if (i == n - 1) {
                        printf("Buffer is full\n");
                        array_push_back(tab, value);
                        break;
                    } else {
                        array_push_back(tab, value);
                    }

                }
                if( i == n - 1) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}
                }
                if (tab->size > 0) {
                    array_display(tab);
                    printf("\n");
                } else {
                    printf("Buffer is empty\n");
                }

                goto Next;
            }
            case 2: {
                printf("Podaj liczby ktore chcesz usunac: ");
                int i;
                for (i = 0; i < n; i++) {
                    if (scanf("%d", &value) != 1) {
                        array_destroy_struct(&tab);
                        printf("Incorrect input");

                        return 1;
                    }
                    if (value == 0) {
                        break;
                    } else {
                        array_remove_item(tab, value);

                    }
                }
                if( i == n - 1) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}
                }
                if (tab->size > 0) {
                    array_display(tab);
                    printf("\n");
                } else {
                    printf("Buffer is empty\n");
                }

                goto Next;
            }
            case 0: {
                goto EndWhile;
            }
            default: {
                printf("Incorrect input data\n");
                goto Next;
            }

        }
        Next:;
    }
    EndWhile:;


    array_destroy_struct(&tab);

    return 0;
}