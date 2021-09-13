#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    printf("Enter data type:");
    int type;
    if(scanf("%d", &type) ^ 1){
        printf("Incorrect input");
        return 1;
    }

    int ptr_set = 0, ptr_clear = 0;

    switch (type) {
        case 0:{
            printf("Enter a value:");
            uint32_t a,b,d;
            if (scanf("%ud", &a) ^ 1) {
                printf("Incorrect input");
                return 1;
            }
            b = a;
            d = a;
#ifdef COUNT_BITS
            COUNT_BITS(a, &ptr_set, &ptr_clear);
            printf("%d \n", ptr_set);
            printf("%d \n", ptr_clear);
#endif
#ifdef DISPLAY_BITS
            DISPLAY_BITS(b);
            printf("\n");
#endif
#ifdef REVERSE_BITS
            REVERSE_BITS(&d);
#endif
#ifdef DISPLAY_BITS
            DISPLAY_BITS(d);
            printf("\n");
#endif
            break;
        }
        case 1:{
            printf("Enter a value:");
            uint16_t a,b,d;
            if (scanf("%hu", &a) ^ 1) {
                printf("Incorrect input");
                return 1;
            }
            b = a;
            d = a;
#ifdef COUNT_BITS
            COUNT_BITS(a, &ptr_set, &ptr_clear);
            printf("%d \n", ptr_set);
            printf("%d \n", ptr_clear);
#endif

#ifdef DISPLAY_BITS
            DISPLAY_BITS(b);
            printf("\n");
#endif
#ifdef REVERSE_BITS
            REVERSE_BITS(&d);
#endif
#ifdef DISPLAY_BITS
            DISPLAY_BITS(d);
            printf("\n");
#endif

            break;
        }
        case 2:{
            printf("Enter a value:");
            uint64_t a,b,d;
            if (scanf("%lud", &a) ^ 1) {
                printf("Incorrect input");
                return 1;
            }
            b = a;
            d = a;
#ifdef COUNT_BITS

            COUNT_BITS(a, &ptr_set, &ptr_clear);
            printf("%d \n", ptr_set);
            printf("%d \n", ptr_clear);
#endif
#ifdef DISPLAY_BITS
            DISPLAY_BITS(b);
            printf("\n");
#endif
#ifdef REVERSE_BITS
            REVERSE_BITS(&d);
#endif
#ifdef DISPLAY_BITS
            DISPLAY_BITS(d);
            printf("\n");
#endif
            break;
        }
        default:{
            printf("Incorrect input data");
            return 2;
        }
    }

    return 0;
}
