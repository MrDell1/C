#include <stdio.h>
#include "array_06.h"

int main() {
    int n = 0;
    struct array_t tab;

    printf("Podaj rozmiar tablicy");
    if(scanf("%d", &n) != 1){
        printf("Incorrect input");
        return 1;
    }
    else if(n <= 0){
        printf("Incorrect input data");
        return 2;
    }
    int x = array_create(&tab,n);
    if(x > 0){
        if(x == 1){
            printf("Incorrect input data");
            return 2;
        }
        else{
            printf("Failed to allocate memory");
            return 8;
        }
    }
    int value = 0;
    printf("Podaj liczby: ");
    for(int i = 0; i < n; i++){
        if(scanf("%d", &value) != 1){
            array_destroy(&tab);
            printf("Incorrect input");
            return 1;
        }
        if(value == 0){
            break;
        }
        else if(i == n - 1){
            printf("Buffer is full\n");
            array_push_back(&tab, value);
            break;
        }
        else{
            array_push_back(&tab, value);
        }


    }
    if(tab.size > 0) {
        array_display(&tab);
    }
    else{
        printf("Buffer is empty");
    }
    array_destroy(&tab);

    return 0;
}