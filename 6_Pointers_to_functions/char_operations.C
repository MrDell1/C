#include <string.h>
#include <stdlib.h>
#include "char_operations.h"

char *letter_modifier(const char *input, char(*func_name)(const char)){
    if(input == NULL || func_name == NULL){
        return NULL;
    }
    char *mod = (char*)malloc((int)strlen(input) + 1);
    if(mod == NULL){
        return NULL;
    }
    for(int i = 0; i < (int)strlen(input); i++) {
     *(mod + i) = (*func_name)(*(input + i));
    }
    *(mod + strlen(input)) = '\0';


    return mod;
}

char lower_to_upper (char input){

        if ((input) >= 'a' && (input) <= 'z') {
            (input) = (char)((input) - 32);
        }



    return input;
}
char upper_to_lower (char input){

        if ((input) >= 'A' && (input) <= 'Z') {
            (input) = (char) ((input) + 32);

        }

    return input;
}
char space_to_dash (char input){
        if ((input) == ' ') {
            (input) = '_';
        }

    return input;
}
char reverse_letter (char input){

        if ((input) >= 'a' && (input) <= 'z') {
            (input) = (char) ('a' - (input) + 'z');
        }
        else if ((input) >= 'A' && (input) <= 'Z') {
            (input ) = (char) ('A' - (input) + 'Z');
        }


    return input;
}