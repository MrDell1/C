#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

int main() {
    int n = 0;
    struct circular_buffer_t *str , cb;
    str = &cb;

    printf("Podaj rozmiar buffora");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");

        return 1;
    } else if (n <= 0) {
        printf("Incorrect input data");

        return 2;
    }
    int x = circular_buffer_create_struct(&str, n);
    if (x != 0) {
        if (x == 1) {
            printf("Incorect input data");

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
            circular_buffer_destroy_struct(&str);
            return 1;
        }
        switch (o) {
            case 1: {
                int value = 0;
                printf("Podaj liczbe ");
                if (scanf("%d", &value) != 1) {
                    printf("Incorrect input");
                    circular_buffer_destroy_struct(&str);
                    return 1;
                } else {
                    int err = circular_buffer_push_back(str, value);
                    if (err == 1) {
                        printf("Incorrect input");
                        circular_buffer_destroy_struct(&str);
                        return 1;
                    }
                    goto Next;
                }
            }
            case 2: {
                int code;
                int value = circular_buffer_pop_back(str, &code);
                if (code == 0) {
                    printf("%d \n", value);
                    goto Next;
                } else if (code == 1) {
                    printf("Incorrect input");
                    circular_buffer_destroy_struct(&str);
                    return 1;
                } else {
                    printf("Buffer is empty\n");
                    str->end = 0;
                    str->begin = 0;
                    goto Next;
                }
            }
            case 3: {
                int code = 2;
                int value = circular_buffer_pop_front(str, &code);
                if (code == 0) {
                    printf("%d \n", value);
                    goto Next;
                } else if (code == 1) {
                    printf("Incorrect input");
                    circular_buffer_destroy_struct(&str);
                    return 1;
                } else {
                    printf("Buffer is empty\n");
                    str->end = 0;
                    str->begin = 0;
                    goto Next;
                }
            }
            case 4: {
                int err = circular_buffer_empty(str);
                if (err == 0) {
                    circular_buffer_display(str);
                    goto Next;
                } else if (err == -1) {
                    printf("Incorrect input");
                    circular_buffer_destroy_struct(&str);
                    return 1;
                } else {
                    printf("Buffer is empty\n");
                    str->end = 0;
                    str->begin = 0;
                    goto Next;
                }
            }
            case 5: {
                printf("%d \n", circular_buffer_empty(str));
                goto Next;
            }
            case 6: {
                printf("%d \n", circular_buffer_full(str));
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
    circular_buffer_destroy_struct(&str);

    return 0;
}