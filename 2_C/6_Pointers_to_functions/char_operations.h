//
// Created by Marcin on 24.05.2021.
//

#ifndef DANTE_CHAR_OPERATIONS_H
#define DANTE_CHAR_OPERATIONS_H
typedef const char*  (*funcs)(const char *);
char *letter_modifier(const char *input, char(*func_name)(const char));
char lower_to_upper (char input);
char upper_to_lower (char input);
char space_to_dash (char input);
char reverse_letter (char input);
#endif //DANTE_CHAR_OPERATIONS_H