#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file_t {
    FILE *f;
    int size;
};

int open_file(struct file_t *f, const char *filename);

struct file_t* find_min(const struct file_t *files, int size);

void close_file(struct file_t *f);

int main() {
    char tab[31];
    struct file_t file_s[5];
    int i = 0;
    printf("Enter file name:");
    char *tab_p;
    tab_p = tab;
    while (fgets(tab, 31, stdin) == tab && *tab_p != '\n') {
        char *p;
        if (p = strchr(tab, '\n')) {
            *p = 0;
        } else {
            scanf("%*[^\n]");
            scanf("%*c");
        }
        if (i < 5) {
            if (open_file((file_s + i), tab) == 0) {
                i++;
            }
        }
    }
    if(i <= 0){
        printf("Couldn't open file");
        return 4;
    }
    printf("Podaj tekst: \n");
    char buf[999];
    fflush(stdin);
    char *pointer;
    pointer = buf;
    while (fgets(buf, 1000, stdin) == buf && *pointer != '\n') {

        struct file_t* min_file = (find_min(file_s, i));
        if(min_file == NULL){
            while(i > 0) {
                close_file(file_s + i - 1);
                i--;
            }
            printf("ERROR stuct = NULL");
            return 5;
        }
        else{
            fwrite(buf, sizeof(char), strlen(buf), min_file->f);
            min_file->size = min_file->size + strlen(buf);
        }

    }

    while(i > 0) {
        close_file(file_s + i - 1);
        i--;
    }

    printf("File save");
    return 0;
}

int open_file(struct file_t *f, const char *filename) {
    if (filename == NULL || f == NULL) {
        return 1;
    }
    f->f = fopen(filename, "ab");
    if (f->f == NULL) {
        return 2;
    }
    fseek(f->f, 0, SEEK_END);
    f->size = ftell(f->f);
    return 0;
}

struct file_t* find_min(const struct file_t *files, int size) {
    int i, x = 0;

    if(size <= 0 || files == NULL){
        return NULL;
    }
    int min = files->size;
    for(i = 0; i < size; i++) {
        if (min > (files+i)->size) {
            min = (files+i)->size;
            x = i;
        }
    }
    return (struct file_t*)(files + x);
}

void close_file(struct file_t *f) {
    if(f != NULL && f->f != NULL) {
        fclose(f->f);
    }
}