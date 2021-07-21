#include <stdio.h>
#include <stdint.h>

int longest_series(unsigned int x);


int main() {

    printf("Enter a value:");
    uint32_t a;
    if (scanf("%ud", &a) ^ 1) {
        printf("Incorrect input");
        return 1;
    }

    printf("Wynik: %d", longest_series(a));



    return 0;


}

int longest_series(unsigned int x){
    int temp_count = 0, count = 0;
    int bit;
    while(x){
        bit = (int)(x & (1 << 0));
        if(bit ^ 0){
            temp_count++;
            if(temp_count >= count) {
                count = temp_count;
            }
        }
        else{
            if(temp_count >= count) {
                count = temp_count;
            }
            temp_count = 0;
        }
        x = (x >> 1);

    }

    return count;
}