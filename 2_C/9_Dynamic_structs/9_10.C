#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

int main() {
    struct doubly_linked_list_t *dll;


    dll = dll_create();
    if(dll == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    int o;
    while (1) {
        printf("Co chcesz zrobić");
        if (scanf("%d", &o) != 1) {
            printf("Incorrect input");
            dll_clear(dll);
            free(dll);
            dll = NULL;
            return 1;
        }
        switch (o) {
            case 1: {
                int value = 0;
                printf("Podaj liczbe ");
                if (scanf("%d", &value) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    dll = NULL;
                    return 1;
                } else {
                    int err = dll_push_back(dll, value);
                    if (err == 1) {
                        printf("Incorrect input");
                        dll_clear(dll);
                        free(dll);
                        dll = NULL;
                        return 1;
                    }
                    else if(err == 2){
                        printf("Failed to allocate memory");
                        dll_clear(dll);
                        free(dll);
                        dll = NULL;
                        return 8;
                    }
                    goto Next;
                }
            }
            case 2: {
                if(dll_is_empty(dll) == 1){
                    printf("List is empty\n");
                    goto Next;
                }
                int code;
                int value = dll_pop_back(dll, &code);
                if (code == 0) {
                    printf("%d \n", value);
                    goto Next;
                } else if (code == 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    dll = NULL;
                    return 1;
                } else {
                    printf("Buffer is empty\n");
                    dll->head = NULL;
                    dll->tail = NULL;
                }
                goto Next;
            }
            case 3: {
                int value = 0;
                printf("Podaj liczbe ");
                if (scanf("%d", &value) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    dll = NULL;
                    return 1;
                } else {
                    int err = dll_push_front(dll, value);
                    if (err == 1) {
                        printf("Incorrect input");
                        dll_clear(dll);
                        free(dll);
                        dll = NULL;
                        return 1;
                    }
                    else if(err == 2){
                        printf("Failed to allocate memory");
                        dll_clear(dll);
                        free(dll);
                        dll = NULL;
                        return 8;
                    }
                    goto Next;
                }
            }
            case 4: {
                if(dll_is_empty(dll) == 1){
                    printf("List is empty\n");
                    goto Next;
                }
                int code;
                int value = dll_pop_front(dll, &code);
                if (code == 0) {
                    printf("%d \n", value);
                    goto Next;
                } else if (code == 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    dll = NULL;
                    return 1;
                } else {
                    printf("Buffer is empty\n");
                    dll->head = NULL;
                    dll->tail = NULL;
                    goto Next;
                }
            }
            case 5: {
                int value = 0, index = 0;
                printf("Podaj liczbe ");
                if (scanf("%d", &value) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    dll = NULL;
                    return 1;
                }
                printf("Podaj index ");
                if (scanf("%d", &index) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    dll = NULL;
                    return 1;
                } else {
                    int err = dll_insert(dll, index,value);
                    if (err == 1) {
                        printf("Index out of range\n");
                    }
                    else if(err == 2){
                        printf("Failed to allocate memory");
                        dll_clear(dll);
                        free(dll);
                        dll = NULL;
                        return 8;
                    }

                    goto Next;
                }
            }
            case 6: {
                if(dll_is_empty(dll) == 1){
                    printf("List is empty\n");
                    goto Next;
                }
                int code = 0, index = 0;
                printf("Podaj index ");
                if (scanf("%d", &index) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    dll = NULL;
                    return 1;
                } else {

                    int value = dll_remove(dll, index, &code);
                    if(code == 1){
                        printf("Index out of range\n");
                        goto Next;
                    }
                    printf("%d\n", value);


                    goto Next;
                }
            }
            case 7: {
                if(dll_is_empty(dll) == 1){
                    printf("List is empty\n");
                    goto Next;
                }
                printf("%d \n", dll->tail->data);
                goto Next;
            }
            case 8: {
                if(dll_is_empty(dll) == 1){
                    printf("List is empty\n");
                    goto Next;
                }
                printf("%d \n", dll->head->data);
                goto Next;
            }
            case 9: {
                if(dll_is_empty(dll) == 1){
                    printf("1\n");
                    goto Next;
                }
                else{
                    printf("0\n");
                    goto Next;
                }
            }
            case 10: {
                if(dll_is_empty(dll) == 1){
                    printf("0\n");
                    goto Next;
                }
                printf("%d \n", dll_size(dll));
                goto Next;
            }
            case 11: {
                dll_clear(dll);

                goto Next;
            }
            case 12: {
                if(dll_is_empty(dll) == 1){
                    printf("List is empty\n");
                }
                else {
                    int index = 0, code = 0;
                    printf("Podaj index ");
                    if (scanf("%d", &index) != 1) {
                        printf("Incorrect input");
                        dll_clear(dll);
                        free(dll);
                        dll = NULL;
                        return 1;
                    }
                    if (index > dll_size(dll)) {
                        printf("Index out of range\n");
                    } else {
                        printf("%d\n", dll_at(dll, index, &code));
                    }
                }
                goto Next;
            }
            case 13: {
                if(dll_is_empty(dll) == 1){
                    printf("List is empty\n");
                }
                else {
                    dll_display(dll);
                }
                goto Next;
            }
            case 14: {
                if(dll_is_empty(dll) == 1){
                    printf("List is empty\n");
                }
                else {
                    dll_display_reverse(dll);
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
    if(dll != NULL) {
        dll_clear(dll);
        free(dll);
        dll = NULL;
    }
    return 0;
}