#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils_09.h"


int main() {
    char *tab_p;
    tab_p = (char*)malloc(40);
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
    int x, y, count;
    fflush(stdin);

    printf("How many subimages you want to draw: ");
    if (scanf("%d", &count) != 1) {
        printf("Incorrect input");
        free(tab_p);
        destroy_image(&image);
        return 1;
    }
    if (count <= 0) {
        printf("Incorrect input data");
        free(tab_p);
        destroy_image(&image);
        return 2;
    }
    for (int i = 0; i < count; i++) {
        char *tab_file = (char*)malloc(40);
        if (tab_file == NULL) {
            printf("Failed to allocate memory");
            free(tab_p);
            destroy_image(&image);
            return 8;
        }
        setbuf(stdin, NULL);
        printf("Enter a name of a subimage: ");
        if (fgets(tab_file, 40, stdin) == tab_file) {
            char *p;
            if (p = strchr(tab_file, '\n')) {
                *p = 0;
            }
        }
        setbuf(stdin, NULL);

        struct image_t *sub_img = load_image_t(tab_file, &err);
        if (err == 1 || err == 2) {
            printf("Couldn't open file\n");

            free(tab_file);
            goto Next;
        } else if (err == 3) {
            printf("File corrupted\n");

            free(tab_file);
            goto Next;
        } else if (err == 4) {
            printf("Failed to allocate memory");
            free(tab_file);
            free(tab_p);
            destroy_image(&image);
            return 8;
        }

        printf("Enter coordinates (x, y): ");
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Incorrect input");
            free(tab_file);
            free(tab_p);
            destroy_image(&image);
            destroy_image(&sub_img);
            return 1;
        }
        if (x > image->width || x < 0 || y > image->height || y < 0) {
            printf("Incorrect input data\n");
            destroy_image(&sub_img);
            free(tab_file);
            goto Next;
        }

        int draw = draw_image(image, sub_img, x, y);
        if (draw != 0) {
            printf("Incorrect input data\n");
        }
        destroy_image(&sub_img);
        free(tab_file);
        Next:;

    }




// Name
    char *mod = (char*)malloc(strlen("_modified") + 1);
    if (mod == NULL) {
        printf("Failed to allocate memory");
        destroy_image(&image);
        free(tab_p);
        return 8;
    }
    strcpy(mod, "_modified");


    char *tab_neg = (char*)malloc((strlen(tab_p) + strlen("_modified") + 1));
    if (tab_neg == NULL) {
        printf("Failed to allocate memory");
        destroy_image(&image);
        free(tab_p);
        free(mod);
        return 8;
    }


    char *ext = (char*)malloc(strlen(".txt") + 1);
    if (ext == NULL) {
        printf("Failed to allocate memory");
        destroy_image(&image);
        free(tab_p);
        free(tab_neg);
        free(mod);
        return 8;
    }
    strcpy(ext, ".txt");

    int j;


    char *name = (char*)malloc((strlen(tab_p) - strlen(ext)) + strlen(mod) + 1);
    if (name == NULL) {
        printf("Failed to allocate memory");
        destroy_image(&image);
        free(tab_p);
        free(tab_neg);
        free(mod);
        free(ext);
        return 8;
    }
    int c = (int)(strlen(tab_p)-strlen(ext));
    strncpy(name, tab_p, c);
    j = 0;
    int i;
    for (i = c; i < (int)strlen(mod) + c; i++) {
        *(name + i) = *(mod + j);
        j++;
    }
    *(name + i) = '\0';

    strcpy(tab_neg, name);
    j = 0;
    for (i = (int)strlen(name); i < (int)(strlen(name) + strlen(ext)); i++) {
        *(tab_neg + i) = *(ext + j);
        j++;
    }
    *(tab_neg + i) = '\0';


    if (save_image_t(tab_neg, image) != 0) {
        printf("Couldn't create file\n");
        free(name);
        name = NULL;
        free(ext);
        ext = NULL;
        free(tab_neg);
        tab_neg = NULL;
        free(mod);
        mod = NULL;
        destroy_image(&image);
        free(tab_p);
        tab_p = NULL;
        return 5;
    } else {
        printf("File saved\n");
    }

    free(name);
    name = NULL;
    free(ext);
    ext = NULL;
    free(tab_neg);
    tab_neg = NULL;
    free(mod);
    mod = NULL;
    destroy_image(&image);
    free(tab_p);
    tab_p = NULL;
    return 0;
}