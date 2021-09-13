#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14
enum figure_types{
    TRIANGLE = 1,
    RECTANGLE,
    CIRCLE
};

struct point_t
{
    int x;
    int y;
};
struct rectangle_t
{
    struct point_t p;
    int width;
    int height;
};
struct circle_t
{
    struct point_t c;
    float r;
};
struct triangle_t
{
    struct point_t p1;
    struct point_t p2;
    struct point_t p3;
};
struct figure_t{
    union
    {
        struct rectangle_t rect;
        struct triangle_t triangle;
        struct circle_t circ;
    };
    enum figure_types type;
};

float area_triangle(const struct triangle_t *t);
float area_rectangle(const struct rectangle_t *r);
float area_circle(const struct circle_t *c);
float area_figure(const struct figure_t *f);


void display_rectangle(const struct rectangle_t *rect);
void display_triangle(const struct triangle_t *t);
void display_circle(const struct circle_t *circ);
void display_figure(struct figure_t *f);
int sort_by_area(struct figure_t **figures, int size);

int main() {
    int f, i = 0;


    struct figure_t figure_p[50];

    while(i < 50) {
        printf("Enter figure's type:");
        if(scanf("%d", &f) != 1){
            printf("Incorrect input");
            return 1;
        }
        switch (f) {
            case 1: {
                printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3):");
                int x1, y1, x2, y2, x3, y3;
                if(scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3) != 6){
                    printf("Incorrect input");
                    return 1;
                }

                (figure_p + i)->triangle.p1.x = x1;
                (figure_p + i)->triangle.p1.y = y1;
                (figure_p + i)->triangle.p2.x = x2;
                (figure_p + i)->triangle.p2.y = y2;
                (figure_p + i)->triangle.p3.x = x3;
                (figure_p + i)->triangle.p3.y = y3;
                (figure_p + i)->type = TRIANGLE;
                break;
            }
            case 2: {
                printf("Enter coordinates of a rectangle along with its dimensions (x y width height):");
                int x, y, width, height;
                if(scanf("%d %d %d %d", &x, &y, &width, &height ) != 4){
                    printf("Incorrect input");
                    return 1;
                }
                (figure_p + i)->rect.p.x = x;
                (figure_p + i)->rect.p.y = y;
                (figure_p + i)->rect.width = width;
                (figure_p + i)->rect.height = height;
                (figure_p + i)->type = RECTANGLE;
                break;
            }
            case 3: {
                printf("Enter coordinates and radius of a circle:");
                int x, y;
                float r;
                if(scanf("%d %d %f", &x, &y, &r) != 3){
                    printf("Incorrect input");
                    return 1;
                }
                (figure_p + i)->circ.c.x = x;
                (figure_p + i)->circ.c.y = y;
                (figure_p + i)->circ.r = r;
                (figure_p + i)->type = CIRCLE;
                break;
            }
            case 0: {
                goto EndWhile;
            }
            default:{
                printf("Incorrect input data");
                return 2;
            }
        }
        i++;
    }
    EndWhile: ;

    for(int j = 0; j < i; j++){

        if((figure_p + j)->type == TRIANGLE){
            int x1, y1, x2, y2, x3, y3;
            x1 = (figure_p + j)->triangle.p1.x;
            y1 = (figure_p + j)->triangle.p1.y;
            x2 = (figure_p + j)->triangle.p2.x;
            y2 = (figure_p + j)->triangle.p2.y;
            x3 = (figure_p + j)->triangle.p3.x;
            y3 = (figure_p + j)->triangle.p3.y;
            if(x1 == x2 && y1 == y2 || x1 == x3 && y1 == y3|| x2 == x3 && y2 == y3){
                printf("Incorrect input data");
                return 2;
            }
        }
        else if((figure_p + j)->type == RECTANGLE){
            int width, height;
            width = (figure_p + j)->rect.width;
            height = (figure_p + j)->rect.height;
            if(width < 0 || height < 0){
                printf("Incorrect input data");
                return 2;
            }
        }
        else if((figure_p + j)->type == CIRCLE){
            float r;
            r = (figure_p + j)->circ.r;
            if(r < 0){
                printf("Incorrect input data");
                return 2;
            }
        }

    }
    struct figure_t *structfigure;
    structfigure = figure_p;
    sort_by_area(&structfigure, i);

    for(int j = 0; j < i; j++){
        display_figure((figure_p + j));
    }

    return 0;
}

float area_figure(const struct figure_t *f){
    float P = -1;
    if(f == NULL){
        return -1;
    }
    if(f->type == TRIANGLE){
        P = area_triangle(&(f->triangle));
    }
    else if(f->type == RECTANGLE) {
        P = area_rectangle(&(f->rect));
    }
    else if(f->type == CIRCLE){
        P = area_circle(&(f->circ));
    }
    if(P <= 0){
        return -1;
    }
    return P;
}

float area_triangle(const struct triangle_t *t){
    float P = -1;
    if(t == NULL){
        return -1;
    }
    int x1, y1, x2, y2, x3, y3;
    x1 = t->p1.x;
    y1 = t->p1.y;
    x2 = t->p2.x;
    y2 = t->p2.y;
    x3 = t->p3.x;
    y3 = t->p3.y;

    P = (float)(abs(((x2 - x1)*(y3 - y1)) - ((y2 - y1)*(x3 - x1))))/2;
    if(P <= 0){
        return -1;
    }
    return P;
}

float area_rectangle(const struct rectangle_t *r){
    float P = -1;
    if(r == NULL){
        return -1;
    }
    float width, height;
    width = (float)r->width;
    height = (float)r->height;
    if(width < 0 || height < 0){
        return -1;
    }
    P = width*height;
    if(P <= 0){
        return -1;
    }
    return P;
}

float area_circle(const struct circle_t *c){
    float P = -1;
    if(c == NULL){
        return -1;
    }
    float r;
    r = c->r;
    if(r < 0){
        return -1;
    }
    P = PI * powf(r, 2);
    if(P <= 0){
        return -1;
    }
    return P;
}

int sort_by_area(struct figure_t **figures, int size){
    if(figures == NULL || size <= 0){
        return 1;
    }
    int i, j;

    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - i - 1; j++){
            if(area_figure((*figures + j)) < 0){
                return 1;
            }
            if(area_figure((*figures + j + 1)) < 0){
                return 1;
            }
            if(area_figure((*figures + j)) < area_figure((*figures + j + 1))){
                struct figure_t temp = *(*figures + j);
                *(*figures + j) = *(*figures + j + 1);
                *(*figures + j + 1) = temp;
            }
        }
    }
    return 0;
}


void display_figure(struct figure_t *f){

    if(f->type == TRIANGLE){
        display_triangle(&(f->triangle));
    }
    else if(f->type == RECTANGLE) {
        display_rectangle(&(f->rect));
    }
    else if(f->type == CIRCLE){
        display_circle(&(f->circ));
    }
}
void display_rectangle(const struct rectangle_t *rect){
    printf("Rectangle (%d, %d), width = %d, height = %d \n", rect->p.x, rect->p.y, rect->width, rect->height);
}
void display_triangle(const struct triangle_t *t){
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d) \n", t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
}
void display_circle(const struct circle_t *circ){
    printf("Circle (%d, %d), radius = %f \n", circ->c.x, circ->c.y, circ->r);
}