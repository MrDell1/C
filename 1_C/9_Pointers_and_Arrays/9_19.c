#include<stdio.h>
#include "vector_utils.h"
#include "tested_declarations.h"
#include "rdebug.h"
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int reverse_vector(int* tab, int size){
    if(tab == NULL || size <=0){
        return 1;
    }
    int * tab2 =  (tab + size - 1);
    while (tab < tab2) {
        swap(tab, tab2);
        tab++;
        tab2--;
    }
    return 0;
}








int main() {
    int  T[100];
    int  * x = T;


    printf("Wpisuj wartosci calkowite\n");
    int size = read_vector(x,100,0);
    if(size == -2){
        printf("Incorrect input");
        return 1;
    }

    else if(size == 0 || size == -1){
        printf("Not enough data available");
        return 3;
    }

    display_vector(x, size);
    reverse_vector(x, size);
    printf("\n");
    display_vector(x, size);

    return 0;

}
