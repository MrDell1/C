#include<stdio.h>
int swap(int* a, int* b){
    if(a == NULL || b == NULL){
        return 1;
    }
    int temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}
int main() {
    int a, b;
    int *a_p = &a, *b_p = &b;

    printf("Wpisuj wartosci calkowite\n");
    if(scanf("%d %d", a_p, b_p) != 2){
        printf("Incorrect input");
        return 1;
    }

    swap(a_p, b_p);
    printf("a: %d, b: %d", *a_p, *b_p);

    return 0;

}