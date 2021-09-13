#include <stdio.h>
#include "array_07.h"


int main() {
    int n = 0;
    struct array_t tab, odd, even;

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
    int i;
    printf("Podaj liczby: ");
    for( i = 0; i < n + 1; i++){
        if(scanf("%d", &value) != 1){
            array_destroy(&tab);
            printf("Incorrect input");
            return 1;
        }
        if(value == 0){
            break;
        }
        else if(i == n ){
            printf("Buffer is full\n");
            array_push_back(&tab, value);
            break;
        }
        else{
            array_push_back(&tab, value);
        }

    }

    if(i == 0){
        printf("Not enough data available");
        array_destroy(&tab);
        return 3;
    }
    int err = array_separate(&tab, &odd, &even);
    if(err == 0){
        printf("Failed to allocate memory");
        array_destroy(&tab);
        return 8;
    }
    else if(err == 1){
       //array_display(&tab);
        array_display(&odd);
        printf("Buffer is empty\n");
        array_destroy(&tab);
        array_destroy(&odd);
    }
    else if(err == 2){
        //array_display(&tab);
        printf("Buffer is empty\n");
        array_display(&even);
        array_destroy(&tab);
        array_destroy(&even);
    }
    else{
        //array_display(&tab);
        array_display(&odd);
        array_display(&even);
        array_destroy(&tab);
        array_destroy(&odd);
        array_destroy(&even);
    }


    return 0;
}