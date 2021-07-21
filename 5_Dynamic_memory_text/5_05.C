#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "big_numbers.h"

int main() {
    struct big_numbers_t *bn;

    if (create_big_numbers(&bn, 10) != 0) {
        printf("Failed to allocate memory");
        return 8;
    }
    char *tab =  calloc(201, 1);
    if (tab == NULL) {
        printf("Failed to allocate memory");
        destroy_big_numbers(&bn);
        return 8;
    }

    printf("Podaj liczby:");
    for (int i = 0; i <= 10; i++) {
        if (i >= 10) {
            printf("Buffer is full\n");
            free(tab);
            break;
        }
        //strncpy(tab, "", 1);
        fgets(tab, 201, stdin);
        char *ch = strchr(tab, '\n');
        if(ch != NULL) {
            *(tab + (ch - tab)) = '\0';
        }
       // scanf("%200[^\n]s", (tab));
        if(*(tab + 0) == '\0'){
            free(tab);
            break;
        }
        int err = add_big_number(bn, tab);
        if (err != 0) {
            if (err == 2) {
                printf("Failed to allocate memory\n");
                if (bn->size != 0) {
                    display(bn);
                }
                free(tab);
                destroy_big_numbers(&bn);
                return 0;
            }
            else {
                printf("Incorrect input\n");
            }

        }
        if((int)strlen(tab) == 200){
            char c;
            while((c = getchar()) != '\n' && c != EOF);
        }

    }

    if (bn->size != 0) {
        display(bn);
    } else {
        printf("Buffer is empty");
    }

    destroy_big_numbers(&bn);
    return 0;
}