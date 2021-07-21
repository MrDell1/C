#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct entry_t {
    char name[20];
    char last_name[40];
    int number;
};

void display(const struct entry_t *p);

int load_phonebook_t(const char *filename, struct entry_t *p, int size);

const struct entry_t *find_by_last_name(const struct entry_t *p, int size, const char *last_name);


int main() {
    char tab_input[100], last_name[50];
    struct entry_t entry[10];

    printf("Enter file name:");
    fgets(tab_input, 100, stdin);
    char *p;
    if (p = strchr(tab_input, '\n')) {
        *p = 0;
    } else {
        scanf("%*[^\n]");
        scanf("%*c");
    }

    int records = load_phonebook_t(tab_input, entry, 10);
    if (records <= 0) {
        if (records == 0) {
            printf("File corrupted");
            return 6;
        } else {
            printf("Couldn't open file");
            return 4;
        }
    }


    printf("Enter last name:");
    fgets(last_name, 50, stdin);
    char *g;
    if (g = strchr(last_name, '\n')) {
        *g = 0;
    } else {
        scanf("%*[^\n]");
        scanf("%*c");
    }
    const struct entry_t *found_last_name = find_by_last_name(entry, records, last_name);
    if(found_last_name == NULL){
        printf("Couldn't find name");
    }else {
        display(found_last_name);
    }
    return 0;
}

int load_phonebook_t(const char *filename, struct entry_t *p, int size) {
    if (filename == NULL || p == NULL || size <= 0) {
        return -1;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -2;
    }

    int i, rows = 0;
    char buff[100];
    while(!feof(file)){
        char eol;
        fscanf(file, "%c", &eol);
        if(eol == '\n'){
            rows++;
        }
    }
    fseek(file, 0, SEEK_SET);
    int good_rows = 0;
    for (i = 0; i <= rows; i++) {
        if(size == 0){
            break;
        }

        fgets(buff, 100, file);
        int j = 0;
        char *ptr = strtok(buff, "|");
        while(j < 3){
            if(ptr == NULL){
                goto NextRow;
            }

            if(j == 0){
                strcpy(p->name,ptr);
                int x = strlen(p->name) - 1;
                *(p->name + x) = '\0';
            }

            else if( j == 1){
                ptr = strtok(NULL, "|");
                if(ptr == NULL){
                    goto NextRow;
                }
                strcpy(p->last_name,ptr);

                int x = strlen(p->last_name) - 1;
                *(p->last_name + x) = '\0';
                for(int k = 0; k < (int)strlen(p->last_name); k++) {
                    *(p->last_name + k) = *(p->last_name + k + 1);
                }
            }

            else if(j == 2){
                ptr = strtok(NULL, "|");
                if(ptr == NULL){
                    goto NextRow;;
                }
                p->number = atoi(ptr);
            }

            j++;
        }

        p++;
        size--;
        good_rows++;
        NextRow:;
    }

    fclose(file);
    return good_rows;
}

const struct entry_t *find_by_last_name(const struct entry_t *p, int size, const char *last_name) {
    if (p == NULL || size <= 0 || last_name == NULL) {
        return NULL;
    }
    while (size > 0) {
        if (strcmp(p->last_name, last_name) == 0) {
            return p;
        }
        p++;
        size--;
    }

    return NULL;
}

void display(const struct entry_t *p) {
    if (p == NULL) {

    } else {
        printf("Name: %s\n", p->name);
        printf("Last name: %s\n", p->last_name);
        printf("Phone number: %d\n", p->number);
    }
}