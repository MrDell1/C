#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils_07.h"

struct image_t *load_image_t(const char *filename, int *err_code) {
    if (filename == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return NULL;
    }
    struct image_t *img = (struct image_t*)malloc(sizeof(struct image_t));
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

struct image_t *image_flip_horizontal(const struct image_t *m1) {
    if (m1 == NULL || m1->height <= 0 || m1->width <= 0 || m1->ptr == NULL) {
        return NULL;
    }

    struct image_t *horizontal_m = (struct image_t *)malloc(sizeof(struct image_t));
    if (horizontal_m == NULL) {

        return NULL;
    }
    horizontal_m->width = m1->width;
    horizontal_m->height = m1->height;
    strcpy(horizontal_m->type, m1->type);

    horizontal_m->ptr = (int**)malloc(m1->height * 2 * sizeof(int));

    if (horizontal_m->ptr == NULL) {
        free(horizontal_m);
        return NULL;
    }
    for (int i = 0; i < m1->height; i++) {
        *(horizontal_m->ptr + i) = (int*)malloc(m1->width * sizeof(int));
        if (*(horizontal_m->ptr + i) == NULL) {
            for (int c = i - 1; c >= 0; c--) {
                free(*(horizontal_m->ptr + c));
            }
            free(horizontal_m->ptr);
            free(horizontal_m);
            return NULL;
        }
    }

    int temp;
    if(m1->height % 2 == 0) {
        for (int i = 0; i < (int) (m1->height / 2); i++) {
            for (int j = 0; j < m1->width; j++) {
                temp = *(*(m1->ptr + i) + j);
                *(*(horizontal_m->ptr + i) + j) = *(*(m1->ptr + (m1->height - i - 1)) + j);
                *(*(horizontal_m->ptr + (m1->height - i - 1)) + j) = temp;
            }
        }
    }
    else{
        for (int i = 0; i <= (int) (m1->height / 2); i++) {
            for (int j = 0; j < m1->width; j++) {
                temp = *(*(m1->ptr + i) + j);
                *(*(horizontal_m->ptr + i) + j) = *(*(m1->ptr + (m1->height - i - 1)) + j);
                *(*(horizontal_m->ptr + (m1->height - i - 1)) + j) = temp;
            }
        }
    }

    return (struct image_t *) horizontal_m;
}

struct image_t *image_flip_vertical(const struct image_t *m1) {
    if (m1 == NULL || m1->height <= 0 || m1->width <= 0 || m1->ptr == NULL) {
        return NULL;
    }

    struct image_t *vartical_m = (struct image_t *)malloc(sizeof(struct image_t));
    if (vartical_m == NULL) {
        return NULL;
    }
    vartical_m->width = m1->width;
    vartical_m->height = m1->height;
    strcpy(vartical_m->type, m1->type);

    vartical_m->ptr = (int**)malloc(m1->height * 2 * sizeof(int));

    if (vartical_m->ptr == NULL) {
        free(vartical_m);
        return NULL;
    }
    for (int i = 0; i < m1->height; i++) {
        *(vartical_m->ptr + i) = (int*)malloc(m1->width * sizeof(int));
        if (*(vartical_m->ptr + i) == NULL) {
            for (int c = i - 1; c >= 0; c--) {
                free(*(vartical_m->ptr + c));
            }
            free(vartical_m->ptr);
            free(vartical_m);
            return NULL;
        }
    }

    int temp;
    if(m1->width % 2 == 0) {
        for (int i = 0; i < m1->height; i++) {
            for (int j = 0; j < (int) (m1->width / 2); j++) {
                temp = *(*(m1->ptr + i) + j);
                *(*(vartical_m->ptr + i) + j) = *(*(m1->ptr + i) + (m1->width - j - 1));
                *(*(vartical_m->ptr + i) + (m1->width - j - 1)) = temp;
            }
        }
    }
    else{
        for (int i = 0; i < m1->height; i++) {
            for (int j = 0; j <= (int) (m1->width / 2); j++) {
                temp = *(*(m1->ptr + i) + j);
                *(*(vartical_m->ptr + i) + j) = *(*(m1->ptr + i) + (m1->width - j - 1));
                *(*(vartical_m->ptr + i) + (m1->width - j - 1)) = temp;
            }
        }
    }


    return (struct image_t *) vartical_m;

}

struct image_t *image_negate(const struct image_t *m1) {
    if (m1 == NULL || m1->height <= 0 || m1->width <= 0 || m1->ptr == NULL) {
        return NULL;
    }

    struct image_t *negative_m = (struct image_t *)malloc(sizeof(struct image_t));
    if (negative_m == NULL) {
        return NULL;
    }
    negative_m->width = m1->width;
    negative_m->height = m1->height;
    strcpy(negative_m->type, m1->type);

    negative_m->ptr = (int**)malloc(m1->height * 2 * sizeof(int));

    if (negative_m->ptr == NULL) {
        free(negative_m);
        return NULL;
    }
    for (int i = 0; i < m1->height; i++) {
        *(negative_m->ptr + i) = (int*)malloc(m1->width * sizeof(int));
        if (*(negative_m->ptr + i) == NULL) {
            for (int c = i - 1; c >= 0; c--) {
                free(*(negative_m->ptr + c));
            }
            free(negative_m->ptr);
            free(negative_m);
            return NULL;
        }
    }


    for (int i = 0; i < m1->height; i++) {
        for (int j = 0; j < m1->width; j++) {
            *(*(negative_m->ptr + i) + j) = 255 - *(*(m1->ptr + i) + j);

        }
    }

    return (struct image_t *) negative_m;
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