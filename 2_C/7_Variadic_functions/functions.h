//
// Created by Marcin on 27.05.2021.
//

#ifndef DANTE_FUNCTIONS_H
#define DANTE_FUNCTIONS_H
typedef char * (*func)(const char *);
char **text_modifier(const char  *text, int count, ...);
char *lower_to_upper (const char *in);
char *upper_to_lower (const char *in);
char *space_to_dash (const char *in);
char *reverse_letter (const char *in);
void free_texts(char **);
#endif //DANTE_FUNCTIONS_H