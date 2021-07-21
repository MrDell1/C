#include <stdio.h>
#include <stdint.h>

int is_sparse(uint64_t value);


int main() {

    printf("Enter a value:");
    uint64_t  a;
    if (scanf("%lu", &a) ^ 1) {
        printf("Incorrect input");
        return 1;
    }

    printf("Liczaba: %016lx, Wynik: %d", a, is_sparse(a));



    return 0;


}

int is_sparse(uint64_t value){
    int count = 0;
    int bit;
    while(value){
        bit = (int)(value & (1 << 0));
        if(bit ^ 0){
            count++;
        }
        else{
            count = 0;
        }
        if(count ^ 0){
            if (count ^ 1){
                return 0;
            }
        }
        value = (value >> 1);

    }

    return 1;
}