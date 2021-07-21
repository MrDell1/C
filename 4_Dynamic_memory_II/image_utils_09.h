//
// Created by Marcin on 20.05.2021.
//

#ifndef DANTE_IMAGE_UTILS_H
#define DANTE_IMAGE_UTILS_H
struct image_t {
    char type[3];
    int **ptr;
    int width;
    int height;
};



struct image_t *load_image_t(const char *filename, int *err_code);

int save_image_t(const char *filename, const struct image_t *m1);

void destroy_image(struct image_t **m);
int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty);
const int* image_get_pixel(const struct image_t *img, int x, int y);
int* image_set_pixel(struct image_t *img, int x, int y);


#endif //DANTE_IMAGE_UTILS_H