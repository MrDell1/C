#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils_08.h"

int main() {
    char *tab_p;
    tab_p = (char*)malloc(sizeof(char) * 40);
    if (tab_p == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter file name: ");
    if (fgets(tab_p, 40, stdin) == tab_p) {
        char *p;
        if (p = strchr(tab_p, '\n')) {
            *p = 0;
        }
    }
    setbuf(stdin, NULL);
   

    int err;
    struct image_t *image = load_image_t(tab_p, &err);
    if (err == 1) {
        printf("Couldn't open file");
        free(tab_p);
        return 4;
    } else if (err == 2) {
        printf("Couldn't open file");
        free(tab_p);
        return 4;
    } else if (err == 3) {
        printf("File corrupted");
        free(tab_p);
        return 6;
    } else if (err == 4) {
        printf("Failed to allocate memory");
        free(tab_p);
        return 8;
    }
    int width, height, x, y, value;
    fflush(stdin);
    printf("Podaj wspolrzedne i wymiary prostokata: ");
    if(scanf("%d %d %d %d", &x, &y, &width, &height) != 4){
        printf("Incorrect input");
        free(tab_p);
        destroy_image(&image);
        return 1;
    }

    struct rectangle_t *rec = (struct rectangle_t *)malloc(sizeof(struct rectangle_t));
    if(rec == NULL){
        printf("Failed to allocate memory");
        free(tab_p);
        destroy_image(&image);
        return 8;
    }
    rec->p.x = x;
    rec->p.y = y;
    rec->width = width;
    rec->height = height;
    printf("Podaj kolor: ");
    if(scanf("%d", &value) != 1){
        printf("Incorrect input");
        free(tab_p);
        destroy_image(&image);
        free(rec);
        return 1;
    }
    if(image_draw_rectangle(image, rec, value) != 0){
        free(rec);
        destroy_image(&image);
        free(tab_p);
        printf("Incorrect input data");
        return 2;
    }

    if(save_image_t(tab_p, image) != 0){
        free(rec);
        destroy_image(&image);
        free(tab_p);
        printf("Couldn't create file");
        return 5;
    }
    else{
        printf("File saved");
    }

    free(rec);
    destroy_image(&image);
    free(tab_p);
    tab_p = NULL;


    return 0;
}