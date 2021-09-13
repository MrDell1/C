#include <stdio.h>

int read_vector_float(float * tab, int size, float stop_value){
    if (size <= 0 || tab == NULL) {
        return -1;
    }
    int licznik = 0;
    for (int i = 0; i < size; i++) {
        if( scanf("%f", tab + i) != 1){
            return -2;
        }
        if (*(tab + i) == stop_value) {
            break;
        }
        licznik++;
    }
    return licznik;
}
void display_vector(const int* tab, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", *tab);
        tab ++;
    }
}

