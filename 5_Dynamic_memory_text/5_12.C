#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_words(const char *text);
int sort_words(char **words);
void destroy(char **words);
void display(char **words);
static int myCompare(const void* a, const void* b);


int main() {
    char *text = (char*)calloc(1000, 1);
    if(text == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter text:");
    fgets(text, 1000, stdin);
    if((int) strlen(text) == 0){
        printf("Nothing to show");
        free(text);
        return 0;
    }
    int j = 0;
    for(int i = 0; i <= (int)strlen(text); i++) {
        if ((*(text + i) >= 65 && *(text + i) <= 90) || (*(text + i) >= 97 && *(text + i) <= 122)) {
            j++;
        }
    }
    if(j == 0){
        printf("Nothing to show");
        free(text);
        return 0;
    }

    char ** words = split_words(text);
    if(words == NULL){
        printf("Failed to allocate memory");
        free(text);
        return 8;
    }
    sort_words(words);

    display(words);
    destroy(words);
    free(text);
    return 0;
}

char **split_words(const char *text){
    if(text == NULL){
        return NULL;
    }
    if((int) strlen(text) == 0){
        return NULL;
    }
    int count_words = 0;

    char ** words = (char **)calloc(1, sizeof(char*));
    if(words == NULL){
        return NULL;
    }

    int j = 0;

    for(int i = 0; i <= (int)strlen(text); i++){
        if((*(text + i) >= 65 && *(text + i) <= 90) || (*(text + i) >=97 && *(text + i) <= 122)){
            j++;
        }
        else if(j != 0) {
            *(words + count_words) = (char *)calloc(j + 1, 1);
            if(*(words + count_words) == NULL){
                for(int c = count_words - 1; c >= 0; c--){
                    free(*(words + c));
                }
                free(words);
                return NULL;
            }
            int k = 0;
            for(int x = i - j; x < i; x++) {
                const char ch = *(text + x);
                strncpy((*(words + count_words) + k), &ch, 1);
                k++;
            }

            count_words++;
            char ** temp_words;
            temp_words = (char **)realloc(words, (count_words + 1) * sizeof(char *));
            if (temp_words == NULL) {
                for(int c = count_words - 1; c >= 0; c--){
                    free(*(words + c));
                }
                free(words);
                //ZWOLINJ
                return NULL;
            }
            words = temp_words;
            j = 0;

            //*(words + count_words) = NULL;
        }
    }
    if(count_words == 0){
        free(words);
        return NULL;
    }
    *(words + count_words) = NULL;

    return words;

}

int sort_words(char **words){
    if(words == NULL){
        return 1;
    }
    int count = 0;
    while (*(words + count) != NULL){
        count++;
    }
    qsort(words, count, sizeof(char*), myCompare);

    return 0;
}

static int myCompare(const void* a, const void* b){

return strcmp(*(const char**)a, *(const char**)b);
}

void display(char **words){
    if(words != NULL){
        int i = 0;
        while(*(words + i) != NULL){
            printf("%s\n", *(words + i));
            i++;
        }
    }
}

void destroy(char **words){
    if(words != NULL) {
        int i = 0;
        while (*(words + i) != NULL) {
            free(*(words + i));
            *(words + i) = NULL;
            i++;
        }
        free(*(words + i));
        *(words + i) = NULL;
        if (words != NULL) {
            free(words);
            words = NULL;
        }
    }
}