//
// Created by Marcin on 27.05.2021.
//

#ifndef DANTE_FUNCTIONS_H
#define DANTE_FUNCTIONS_H

#define COUNT_BITS(value, pointer_to_bits_set_counter, pointer_to_bits_cleared_counter) { \
    int bit, *ser_ptr = pointer_to_bits_set_counter, *clear_ptr = pointer_to_bits_cleared_counter,  i = sizeof(value)*8; \
    if(i ^ 64){                                                                           \
        if(i ^ 32){                                                                       \
            unsigned short x = value;                                                     \
            *ser_ptr = 0;                                                                 \
    *clear_ptr = 0;                                                                       \
   while(i > 0){                                                                          \
    bit = (int) ((x) & (1 << 0));                                                         \
   if(bit ^ 0){                                                                           \
    *ser_ptr+=1;                                                                          \
    }                                                                                     \
    else{                                                                                 \
        *clear_ptr+=1;                                                                    \
    }                                                                                     \
    (x) = ((x) >> 1);                                                                     \
    i--;                                                                                  \
    }                                                                                     \
        }                                                                                 \
        else{                                                                             \
            unsigned int x = value;                                                       \
            *ser_ptr = 0;                                                                 \
    *clear_ptr = 0;                                                                       \
   while(i > 0){                                                                          \
    bit = (int) ((x) & (1 << 0));                                                         \
   if(bit ^ 0){                                                                           \
    *ser_ptr+=1;                                                                          \
    }                                                                                     \
    else{                                                                                 \
        *clear_ptr+=1;                                                                    \
    }                                                                                     \
    (x) = ((x) >> 1);                                                                     \
    i--;                                                                                  \
    }                                                                                     \
        }                                                                                 \
    }                                                                                     \
    else{                                                                                 \
        unsigned long  x = value;                                                         \
        *ser_ptr = 0;                                                                     \
    *clear_ptr = 0;                                                                       \
   while(i > 0){                                                                          \
    bit = (int) ((x) & (1 << 0));                                                         \
   if(bit ^ 0){                                                                           \
    *ser_ptr+=1;                                                                          \
    }                                                                                     \
    else{                                                                                 \
        *clear_ptr+=1;                                                                    \
    }                                                                                     \
    (x) = ((x) >> 1);                                                                     \
    i--;                                                                                  \
    }                                                                                     \
}                                                                                         \
}

#define DISPLAY_BITS(value){                                                              \
    int bit, i = sizeof(value)*8;                                                         \
    char *str = malloc(sizeof(value)*8 + 1);                                              \
    if(i ^ 64){                                                                           \
        if(i ^ 32){                                                                       \
             unsigned short x = value;                                                    \
             while(i >= 0){                                                               \
   if(i ^ sizeof(value)*8 ){                                                              \
   bit = (int)(x & (1 << 0));                                                             \
    if(bit ^ 0){                                                                          \
        *(str + i) = 49;                                                                  \
    }                                                                                     \
    else{                                                                                 \
        *(str + i) = 48;                                                                  \
    }                                                                                     \
    x = (x >> 1);                                                                         \
   }                                                                                      \
   else{                                                                                  \
        *(str + i) = '\0';                                                                \
   }                                                                                      \
    i--;                                                                                  \
    }                                                                                     \
        }                                                                                 \
        else{                                                                             \
        unsigned int x = value;                                                           \
        while(i >= 0){                                                                    \
   if(i ^ sizeof(value)*8 ){                                                              \
   bit = (int)(x & (1 << 0));                                                             \
    if(bit ^ 0){                                                                          \
        *(str + i) = 49;                                                                  \
    }                                                                                     \
    else{                                                                                 \
        *(str + i) = 48;                                                                  \
    }                                                                                     \
    x = (x >> 1);                                                                         \
   }                                                                                      \
   else{                                                                                  \
        *(str + i) = '\0';                                                                \
   }                                                                                      \
    i--;                                                                                  \
    }                                                                                     \
        }                                                                                 \
    }                                                                                     \
    else{                                                                                 \
     unsigned long  x = value;                                                            \
while(i >= 0){                                                                            \
   if(i ^ sizeof(value)*8 ){                                                              \
   bit = (int)(x & (1 << 0));                                                             \
    if(bit ^ 0){                                                                          \
        *(str + i) = 49;                                                                  \
    }                                                                                     \
    else{                                                                                 \
        *(str + i) = 48;                                                                  \
    }                                                                                     \
    x = (x >> 1);                                                                         \
   }                                                                                      \
   else{                                                                                  \
        *(str + i) = '\0';                                                                \
   }                                                                                      \
    i--;                                                                                  \
    }                                                                                     \
    }                                                                                     \
    printf("%s", str);                                                                    \
    free(str);                                                                            \
}
#define REVERSE_BITS(pointer_to_variable){                                                \
    int i = sizeof(*pointer_to_variable) * 8;                                             \
   if(i ^ 64){                                                                            \
        if(i ^ 32){                                                                       \
           unsigned short rev = *pointer_to_variable;                                     \
           i--;                                                                           \
            *pointer_to_variable >>= 1;                                                   \
            while(*pointer_to_variable){                                                  \
                rev <<= 1;                                                                \
                rev |= *pointer_to_variable & 1;                                          \
                *pointer_to_variable >>= 1;                                               \
                i--;                                                                      \
            }                                                                             \
            rev <<= i;                                                                    \
            *pointer_to_variable = rev;                                                   \
        }                                                                                 \
        else{                                                                             \
            unsigned int rev = *pointer_to_variable;                                      \
            i--;                                                                          \
            *pointer_to_variable >>= 1;                                                   \
            while(*pointer_to_variable){                                                  \
                rev <<= 1;                                                                \
                rev |= *pointer_to_variable & 1;                                          \
                *pointer_to_variable >>= 1;                                               \
                i--;                                                                      \
            }                                                                             \
            rev <<= i;                                                                    \
            *pointer_to_variable = rev;                                                   \
        }                                                                                 \
   }                                                                                      \
   else{                                                                                  \
        unsigned long  rev = *pointer_to_variable;                                        \
        i--;                                                                              \
            *pointer_to_variable >>= 1;                                                   \
            while(*pointer_to_variable){                                                  \
                rev <<= 1;                                                                \
                rev |= *pointer_to_variable & 1;                                          \
                *pointer_to_variable >>= 1;                                               \
                i--;                                                                      \
            }                                                                             \
            rev <<= i;                                                                    \
            *pointer_to_variable = rev;                                                   \
   }                                                                                      \
}

#endif //DANTE_FUNCTIONS_H