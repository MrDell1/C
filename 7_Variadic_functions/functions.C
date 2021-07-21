#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "functions.h"

char **text_modifier(const char *text, int count, ...) {
    if (text == NULL || count <= 0) {
        return NULL;
    }

    //int buf_size = (int) strlen(text);
    char **out;
    out = (char**)malloc((count + 1) * (sizeof(char *)));
    if (out == NULL) {
        return NULL;
    }


    va_list vaList;
            va_start(vaList, count);
    for (int i = 0; i < count; i++) {
        *(out + i) = va_arg(vaList, func)(text);
        if(*(out + i) == NULL){
            for(int c = i; c >= 0; c--){
                free(*(out + c));
            }
            free(out);
            va_end(vaList);
            return NULL;
        }
    }

    *(out + count) = NULL;
            va_end(vaList);

    return out;
}

char *lower_to_upper(const char *in) {
    char *upper = (char*)malloc(strlen(in) + 1);
    if (upper == NULL) {
        return NULL;
    }
    strcpy(upper, in);
    for (int i = 0; i < (int) strlen(upper); i++) {
        if (*(upper + i) >= 'a' && *(upper + i) <= 'z') {
            *(upper + i) = (char) (*(upper + i) - 32);
        }

    }

    return upper;
}

char *upper_to_lower(const char *in) {
    char *lower = (char*)malloc(strlen(in) + 1);
    if (lower == NULL) {
        return NULL;
    }
    strcpy(lower, in);
    for (int i = 0; i < (int) strlen(lower); i++) {
        if (*(lower + i) >= 'A' && *(lower + i) <= 'Z') {
            *(lower + i) = (char) (*(lower + i) + 32);

        }
    }
    return lower;
}

char *space_to_dash(const char *in) {
    char *output = (char*)malloc(strlen(in) + 1);
    if (output == NULL) {
        return NULL;
    }
    strcpy(output, in);
    for (int i = 0; i < (int) strlen(output); i++) {
        if (*(output + i) == ' ') {
            *(output + i) = '_';
        }
    }
    return output;
}

char *reverse_letter(const char *in) {
    char *reverse = (char*)malloc(strlen(in) + 1);
    if (reverse == NULL) {
        return NULL;
    }
    strcpy(reverse, in);
    for (int i = 0; i < (int) strlen(reverse); i++) {
        if (*(reverse + i) >= 'a' && *(reverse + i) <= 'z') {
            *(reverse + i) = (char) ('a' - *(reverse + i) + 'z');
        } else if (*(reverse + i) >= 'A' && *(reverse + i) <= 'Z') {
            *(reverse + i) = (char) ('A' - *(reverse + i) + 'Z');
        }

    }
    return reverse;
}

void free_texts(char **temp) {
    if (temp != NULL) {
        int i = 0;
        while(*(temp + i) != NULL){
            free(*(temp + i));
            i++;
        }
        free(temp);
    }
}