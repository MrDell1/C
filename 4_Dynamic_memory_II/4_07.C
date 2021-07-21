#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils_07.h"


int main() {
    char *tab_p;
    tab_p = malloc(sizeof(char) * 40);
    if (tab_p == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter file name: ");
    if (fgets(tab_p, 40, stdin) == tab_p) {
        char *p;
        if (p = strchr(tab_p, '\n')) {
            *p = 0;
        } else {

        }
    }
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

    struct image_t *hor = image_flip_horizontal(image);
    if (hor == NULL) {
        printf("Failed to allocate memory");
        destroy_image(&image);
        free(tab_p);
        return 8;
    }
    char *tab_hor = malloc(strlen(tab_p) + strlen("mirror_h_") + 1);
    if (tab_hor == NULL) {
        printf("Failed to allocate memory");
        destroy_image(&image);
        free(tab_p);
        return 8;
    }
    strcpy(tab_hor, "mirror_h_");
    strcat(tab_hor, tab_p);

    if (save_image_t(tab_hor, hor) != 0) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }



    struct image_t *ver = image_flip_vertical(image);
    if (ver == NULL) {
        printf("Failed to allocate memory");
        destroy_image(&image);
        free(tab_p);
        return 8;
    }
    char *tab_ver = malloc(strlen(tab_p) + strlen("mirror_v_") + 1);
    if (tab_ver == NULL) {
        printf("Failed to allocate memory");
        destroy_image(&image);
        free(tab_p);
        return 8;
    }
    strcpy(tab_ver, "mirror_v_");
    strcat(tab_ver, tab_p);

    if (save_image_t(tab_ver, ver) != 0) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }


    struct image_t *neg = image_negate(image);
    if (neg == NULL) {
        printf("Failed to allocate memory");
        destroy_image(&image);
        free(tab_p);
        return 8;
    }
    char *tab_neg = malloc(strlen(tab_p) + strlen("invert_") + 1);
    if (tab_neg == NULL) {
        printf("Failed to allocate memory");
        destroy_image(&image);
        free(tab_p);
        return 8;
    }
    strcpy(tab_neg, "invert_");
    strcat(tab_neg, tab_p);

    if (save_image_t(tab_neg, neg) != 0) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }



    destroy_image(&image);
    destroy_image(&hor);
    destroy_image(&ver);
    destroy_image(&neg);
    free(tab_p);
    tab_p = NULL;
    free(tab_hor);
    tab_hor = NULL;
    free(tab_ver);
    tab_ver = NULL;
    free(tab_neg);
    tab_neg = NULL;

    return 0;
}