#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct message_t
{
    char a;
    double b;
    int c;
};
int load_data(struct message_t *cp, int size, const char *filename);
int decode_message(const struct message_t *cp, int size, char *msg, int text_size);


int main() {
    char tab[31];
    char message_tab[3000];
    struct message_t msg[100];


    printf("Enter file name:");

    fgets(tab, 31, stdin);
    char *p;
    if (p = strchr(tab, '\n')) {
        *p = 0;
    }
    else {
        scanf("%*[^\n]");
        scanf("%*c");
    }

    int str_num = load_data(msg, 100, tab);
    if(str_num == -3){
        printf("File corrupted");
        return 6;
    }
    int err = decode_message(msg, str_num, (char*)message_tab, sizeof(message_tab));

    if(err == 1){
        printf("Couldn't open file");
        return 4;
    }


    printf("%s", message_tab);
    return 0;
}

int load_data(struct message_t *cp, int size, const char *filename){
    if(filename == NULL || cp == NULL || size < 1){
        return -1;
    }
    FILE *file = fopen(filename, "rb");
    if(file == NULL){
        return -2;
    }



    unsigned int x;
    if(fread(&x, sizeof(unsigned int), 1, file) != 1){
        fclose(file);
        return -3;
    }
    if(x % 24 != 0){
        fclose(file);
        return -3;
    }
    x /= sizeof(struct message_t);

    if(x > (unsigned int)size){
        x = (unsigned int)size;
    }
    else if((int)x < 0){
        fclose(file);
        return -3;
    }
    else{
        size = (int)x;
    }

    while (x-- > 0 && fread(cp++, sizeof(struct message_t), 1, file) == 1){

    }

    if (feof(file) != 0 || ferror(file) != 0) {
        fclose(file);
        return -3;
    }

    fclose(file);
    return size;


}
int decode_message(const struct message_t *cp, int size, char *msg, int text_size){
    if(cp == NULL || size < 1 || size > 100 || msg == NULL || text_size < 1){
        return 1;
    }
    int i = 0, x = 0;
    unsigned char *p1 = (unsigned char*)cp;
    while (isalpha(*p1) == 0 && isdigit(*p1) == 0) {
        p1++;
    }
   while(1){
       if(i == size){
           *msg = '\0';
           break;
       }
       i++;
       p1++;
       if(x + 7 >= text_size){
           memcpy(msg, p1, text_size - x);
           msg += text_size-1-x;
           *msg = '\0';
           break;
       }
       memcpy(msg, p1, 7);
       x += 7;
       msg += 7;
       p1 += 19;
       if(x + 4 >= text_size){
           memcpy(msg, p1, text_size - 1);
           msg += text_size-1-x;
           *msg = '\0';
           break;
       }
       memcpy(msg, p1, 4);
       x += 4;
       if(x >= text_size){
           *msg = '\0';
           break;
       }
       msg += 4;
       p1 += 4;
       if(*(p1 - 1) == '\0' || *p1 == '\0'){
           *msg = '\0';
           break;
       }
   }




    return 0;
}