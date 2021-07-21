#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils_09.h"

struct image_t *load_image_t(const char *filename, int *err_code) {
    if (filename == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return NULL;
    }
    struct image_t *img = (struct image_t *)malloc(sizeof(struct image_t));
    if (img == NULL) {
        if (err_code != NULL) {
            *err_code = 4;
        }
        return NULL;
    }
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        if (err_code != NULL) {
            *err_code = 2;
        }
        free(img);
        return NULL;
    }


    fscanf(file, "%s", img->type);
    if (strcmp(img->type, "P2") == 0) {

        int h, w, max;
        if (fscanf(file, "%d", &w) != 1) {
            if (err_code != NULL) {
                *err_code = 3;
            }
            free(img);
            fclose(file);
            return NULL;
        } else {
            if (w <= 0) {
                if (err_code != NULL) {
                    *err_code = 3;
                }
                free(img);
                fclose(file);
                return NULL;
            }
            img->width = w;
        }
        if (fscanf(file, "%d", &h) != 1) {
            if (err_code != NULL) {
                *err_code = 3;
            }
            free(img);
            fclose(file);
            return NULL;
        } else {
            if (h <= 0) {
                if (err_code != NULL) {
                    *err_code = 3;
                }
                free(img);
                fclose(file);
                return NULL;
            }
            img->height = h;
        }
        if (fscanf(file, "%d", &max) != 1) {
            if (err_code != NULL) {
                *err_code = 3;
            }
            free(img);
            fclose(file);
            return NULL;
        } else {
            if (max < 0 || max > 255) {
                if (err_code != NULL) {
                    *err_code = 3;
                }
                free(img);
                fclose(file);
                return NULL;
            }

            img->ptr = (int**)malloc(img->height * 2 * sizeof(int));

            if (img->ptr == NULL) {
                if (err_code != NULL) {
                    *err_code = 4;
                }
                free(img);
                fclose(file);
                return NULL;
            }
            for (int i = 0; i < img->height; i++) {
                *(img->ptr + i) = (int*)malloc(img->width * sizeof(int));
                if (*(img->ptr + i) == NULL) {
                    for (int c = i - 1; c >= 0; c--) {
                        free(*(img->ptr + c));
                    }
                    free(img->ptr);
                    if (err_code != NULL) {
                        *err_code = 4;
                    }
                    free(img);
                    fclose(file);
                    return NULL;
                }
            }

            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    int temp;
                    if (fscanf(file, "%d", &temp) != 1) {
                        if (err_code != NULL) {
                            *err_code = 3;
                        }
                        destroy_image(&img);
                        fclose(file);
                        return NULL;
                    }
                    if (temp > max || temp < 0) {
                        if (err_code != NULL) {
                            *err_code = 3;
                        }
                        destroy_image(&img);
                        fclose(file);
                        return NULL;
                    } else {
                        *(*(img->ptr + i) + j) = temp;
                    }
                }
            }
        }

    } else {
        if (err_code != NULL) {
            *err_code = 3;
        }
        free(img);
        fclose(file);
        return NULL;
    }

    if (err_code != NULL) {
        *err_code = 0;
    }
    fclose(file);
    return (struct image_t *) img;

}

const int *image_get_pixel(const struct image_t *img, int x, int y) {
    if (img == NULL || img->height <= 0 || img->width <= 0|| x < 0 || y < 0 || x >= img->width || y >= img->height) {
        return NULL;
    }
    return &(*(*(img->ptr + y) + x));
}

int *image_set_pixel(struct image_t *img, int x, int y) {
    if (img == NULL || img->height <= 0 || img->width <= 0|| x < 0 || y < 0 || x >= img->width || y >= img->height) {
        return NULL;
    }
    return &(*(*(img->ptr + y) + x));
}

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty){
    if (img == NULL || src == NULL || destx < 0 || destx > img->width || desty < 0 || desty > img->height || src->width <= 0 || src->height <= 0) {
        return 1;
    }

    int width = src->width;
    int height = src->height;
    int img_width = img->width;
    int img_height = img->height;
    int x = destx;
    int y = desty;

    if (width > img_width || height > img_height) {
        return 1;
    }

    if (img_width - x < width || img_height - y < height) {
        return 1;
    }

    int k = 0, z = 0;

    for(int i = y; i < height + y; i++){
        k = 0;
        for(int j = x; j < width + x; j++){
            *image_set_pixel(img, j, i) = *image_get_pixel(src, k, z);
            k++;
        }
        z++;
    }


    return 0;
}



int save_image_t(const char *filename, const struct image_t *m1) {
    if (filename == NULL || m1 == NULL || m1->height <= 0 || m1->width <= 0 || m1->ptr == NULL) {
        return 1;
    }

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        return 2;
    }

    if (fprintf(file, "%s\n", m1->type) < 0) {
        fclose(file);
        return 3;
    }
    if (fprintf(file, "%d %d\n", m1->width, m1->height) < 0) {
        fclose(file);
        return 3;
    }


    fprintf(file, "%d\n", 255);
    for (int i = 0; i < m1->height; i++) {
        for (int j = 0; j < m1->width; j++) {
            if (fprintf(file, "%d ", *(*(m1->ptr + i) + j)) < 0) {
                fclose(file);
                return 3;
            }
        }
        if (fprintf(file, "\n") < 0) {
            fclose(file);
            return 3;
        }
    }
    fclose(file);
    return 0;

}


void destroy_image(struct image_t **m) {
    if (m == NULL) {

    } else {
        for (int i = 0; i < (*m)->height; i++) {
            free(*((*m)->ptr + i));
        }
        free((*m)->ptr);
        free(*m);
        *m = NULL;
    }

}