#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct array_t
{
    int size;
    int array[100];
};
int save_array_b(const char *filename, const struct array_t *arr);
int load_array_b(const char *filename, struct array_t *arr);
int sort(struct array_t *arr);
int main() {
    char tab[31];
    printf("Enter file name:");
    if (fgets(tab, 31, stdin)) {
        char *p;
        if (p = strchr(tab, '\n')) {
            *p = 0;
        } else {
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }
    struct array_t array;
    int err = load_array_b(tab, &array);
    if(err == 1 || err == 2){
        printf("Couldn't open file");
        return 4;
    }
    else if(err == 3){
        printf("File corrupted");
        return 6;
    }

    err = sort(&array);
    if(err == 1){
        printf("Incorrect input data");
        return 2;
    }

    err = save_array_b(tab, &array);
    if(err == 1){
        printf("Couldn't open file");
        return 4;
    }
    else if(err == 2 || err == 3){
        printf("Couldn't create file");
        return 5;
    }
    printf("File saved");
    return 0;
}
int load_array_b(const char *filename, struct array_t *arr){
    if(filename == NULL || arr == NULL){
        return 1;
    }
    FILE *file = fopen(filename, "rb");
    if(file == NULL){
        return 2;
    }



    int x = fread(arr,sizeof(struct array_t), 1, file);

    if(x == 0){
        fclose(file);
        return 3;
    }
    fclose(file);

    return 0;
}


int sort(struct array_t *arr){
    if(arr == NULL || arr->size > 100 || arr->size <= 0){
        return 1;
    }
    int i, j, temp;
    int *p;
    p = arr->array;
    int s = arr->size;
    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1-i); j++)
        {
            if (*(p+j) > *(p+j+1))
            {
                temp = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = temp;
            }

        }

    }
    return 0;
}

int save_array_b(const char *filename, const struct array_t *arr){
    if(filename == NULL || arr == NULL){
        return 1;
    }
    FILE *file = fopen(filename, "wb");
    if(file == NULL){
        return 2;
    }

    fwrite(arr, sizeof(struct array_t), 1, file);

    fclose(file);
    return 0;

}