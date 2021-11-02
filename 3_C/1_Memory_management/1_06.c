#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

struct memory_manager_t {
    void *memory_start;
    size_t memory_size;
    struct memory_chunk_t *first_memory_chunk;
};

struct memory_chunk_t {
    struct memory_chunk_t *prev;
    struct memory_chunk_t *next;
    size_t size;
    int free;
};
struct memory_manager_t memory_manager;

void memory_init(void *address, size_t size);

void *memory_malloc(size_t size);

void memory_free(void *address);

int heap_validate(void);

int main() {
    char *memory[1000];
    memory_init(memory, 1000);

    printf("%lu", memory_manager.memory_size);
    return 0;
}

void memory_init(void *address, size_t size) {
    if (address != NULL) {
        memory_manager = *(struct memory_manager_t *) address;
        memory_manager.memory_start = address;
        memory_manager.memory_size = size;
        char*ptr = (char*)memory_manager.memory_start;
        for(int i = 0; i < (int)size; i++){
            if(ptr){
                *ptr = '0';
            }
            ptr++;
        }
        memory_manager.first_memory_chunk = NULL;
    }

}

void *memory_malloc(size_t size) {


    if (size > 0 && memory_manager.memory_size - sizeof(struct memory_manager_t) >= size + 32 && heap_validate() == 0) {
        struct memory_chunk_t *memory_chunk;


        struct memory_chunk_t *curr = (struct memory_chunk_t *) memory_manager.first_memory_chunk;
        int all_ell_size = sizeof(struct memory_manager_t);
        while (curr) {
            all_ell_size += (int) curr->size + (int) sizeof(struct memory_chunk_t) + 32;
            curr = curr->next;
        }

        curr = (struct memory_chunk_t *) memory_manager.first_memory_chunk;
        if (curr == NULL) {
            memory_manager.first_memory_chunk = (struct memory_chunk_t *) (char *) memory_manager.memory_start;
            memory_chunk = (struct memory_chunk_t *) memory_manager.first_memory_chunk;
            char *ptr = (char *) memory_chunk + sizeof(struct memory_chunk_t);
            for (int i = 0; i < 16; i++) {
                *ptr = '#';
                ptr++;
            }
            memory_chunk->prev = NULL;
            memory_chunk->next = NULL;
            memory_chunk->size = size;
            memory_chunk->free = 0;
            ptr = (char *) memory_chunk + sizeof(struct memory_chunk_t) + size + 16;
            for (int i = 0; i < 16; i++) {
                *ptr = '#';
                ptr++;
            }
            return (char *) memory_manager.first_memory_chunk + sizeof(struct memory_chunk_t) + 16;
        }
        while (curr != NULL) {
              if (curr->free == 1 && curr->size >= size + 32) {
                char *ptr = (char *) curr + sizeof(struct memory_chunk_t);
                for (int i = 0; i < 16; i++) {
                    *ptr = '#';
                    ptr++;
                }
                curr->free = 0;
                curr->size = size;
                ptr += size;
                for (int i = 0; i < 16; i++) {
                    *ptr = '#';
                    ptr++;
                }
                return (char *) curr + sizeof(struct memory_chunk_t) + 16;
            } else if (curr->next == NULL && (int) (memory_manager.memory_size - all_ell_size) >= (int) size + 32) {
                char *next = (char *) curr;
                next = next + curr->size + sizeof(struct memory_chunk_t) + 32;
                curr->next = (struct memory_chunk_t *) (next);
                char *ptr = (char *) curr->next + sizeof(struct memory_chunk_t);
                for (int i = 0; i < 16; i++) {
                    *ptr = '#';
                    ptr++;
                }
                /*char *prev = (char *) curr->next;
                prev = prev - curr->size - sizeof(struct memory_chunk_t) - 32;*/
                curr->next->prev = curr;
                curr->next->next = NULL;
                curr->next->size = size;
                curr->next->free = 0;
                ptr = (char *) curr->next + sizeof(struct memory_chunk_t) + size + 16;
                for (int i = 0; i < 16; i++) {
                    *ptr = '#';
                    ptr++;
                }
                return (char *) curr->next + sizeof(struct memory_chunk_t) + 16;
            }

            curr = curr->next;
        }


    }
    return NULL;

}


void memory_free(void *address) {
    if (address != NULL) {
        address = (void *) ((char *) address - (char *) 0x30);
        if (memory_manager.memory_start <= address && (struct memory_manager_t *) address <=
                                                      (struct memory_manager_t *) (char *) memory_manager.memory_start +
                                                      memory_manager.memory_size && heap_validate() == 0) {
            struct memory_chunk_t *block_to_free = (struct memory_chunk_t *) address;
            //block_to_free--;
            bool good = 0;
            struct memory_chunk_t *curr = memory_manager.first_memory_chunk;
            while (curr != NULL) {
                if (curr == block_to_free) {
                    good = 1;
                    break;
                }
                curr = curr->next;
            }
            if (good == 1) {
                if (block_to_free->next == NULL && block_to_free->prev == NULL) {
                    //block_to_free = NULL;
                    memory_init(memory_manager.memory_start, memory_manager.memory_size);
                    return;
                } else if (block_to_free->next == NULL) {
                    if (block_to_free->prev->free == 1) {
                        if (block_to_free->prev->prev == NULL) {
                            memory_init(memory_manager.memory_start, memory_manager.memory_size);
                            return;
                        } else {
                            char *ptr = (char*)block_to_free->prev + sizeof(struct memory_chunk_t) + block_to_free->prev->size;
                            for(int i = 0; i < 16; i++){
                                if(*ptr == '#'){
                                    *ptr = '0';
                                }
                                ptr ++;
                            }
                            ptr = *ptr + (char*)block_to_free + sizeof(struct memory_chunk_t);
                            for(int i = 0; i < 16; i++){
                                if(*ptr == '#'){
                                    *ptr = '0';
                                }
                                ptr ++;
                            }
                            block_to_free->prev->size = (block_to_free->prev->size + block_to_free->size +
                                                         sizeof(struct memory_chunk_t) + 32);
                            block_to_free->prev->next = block_to_free->next;
                            block_to_free = block_to_free->prev;
                            block_to_free->free = 1;
                            block_to_free->prev->next = NULL;
                            //block_to_free = NULL;
                        }
                    } else {
                        block_to_free->free = 1;
                        block_to_free->size += 32;
                        char *ptr = (char*)block_to_free + sizeof(struct memory_chunk_t);
                        for(int i = 0; i < 16; i++){
                            if(*ptr == '#'){
                                *ptr = '0';
                            }
                            ptr ++;
                        }
                        ptr += block_to_free->size - 32;
                        for(int i = 0; i < 16; i++){
                            if(*ptr == '#'){
                                *ptr = '0';
                            }
                            ptr ++;
                        }
                    }
                } else if (block_to_free->prev == NULL) {
                    block_to_free->free = 1;
                    char *ptr = (char*)block_to_free + sizeof(struct memory_chunk_t);
                    for(int i = 0; i < 16; i++){
                        if(*ptr == '#'){
                            *ptr = '0';
                        }
                        ptr ++;
                    }
                    ptr += block_to_free->size;
                    for(int i = 0; i < 16; i++){
                        if(*ptr == '#'){
                            *ptr = '0';
                        }
                        ptr ++;
                    }
                    block_to_free->size += 32;

                } else {
                    block_to_free->free = 1;
                    block_to_free->size += 32;
                    if (block_to_free->prev->free == 1) {
                        if (block_to_free->prev->prev == NULL && block_to_free->next == NULL) {
                            memory_init(memory_manager.memory_start, memory_manager.memory_size);
                            return;
                        }
                        block_to_free->prev->size = (block_to_free->prev->size + block_to_free->size + sizeof(struct memory_chunk_t));
                        block_to_free->prev->next = block_to_free->next;
                        block_to_free->next->prev = block_to_free->prev;
                        block_to_free = block_to_free->prev;
                    }
                    if (block_to_free->next->free == 1) {
                        if (block_to_free->next->next == NULL && block_to_free->prev == NULL) {
                            memory_init(memory_manager.memory_start, memory_manager.memory_size);
                            return;
                        }
                        block_to_free->size = block_to_free->size + block_to_free->next->size + sizeof(struct memory_chunk_t);
                        block_to_free->next = block_to_free->next->next;
                        if (block_to_free->next != NULL) {
                            block_to_free->next->prev = block_to_free;
                        }
                        return;
                    }
                    char *ptr = (char*)block_to_free + sizeof(struct memory_chunk_t);
                    for(int i = 0; i < 16; i++){
                        if(*ptr == '#'){
                            *ptr = '0';
                        }
                        ptr ++;
                    }
                    ptr += block_to_free->size - 32;
                    for(int i = 0; i < 16; i++){
                        if(*ptr == '#'){
                            *ptr = '0';
                        }
                        ptr ++;
                    }

                    if ((unsigned long long) (char *) block_to_free->next - (unsigned long long) (char *) block_to_free - sizeof(struct memory_chunk_t) != (unsigned long long) block_to_free->size) {
                        block_to_free->size = (unsigned long long) (char *) block_to_free->next - (unsigned long long) (char *) block_to_free - (unsigned long long) sizeof(struct memory_chunk_t);
                    }

                }
            }
        }
    }
}


int heap_validate(void) {
    struct memory_chunk_t *check = (struct memory_chunk_t *) memory_manager.first_memory_chunk;
    while (check) {
        if (check->free != 1) {
            char *ptr = (char *) check + sizeof(struct memory_chunk_t);
            int control = 0;
            for (int i = 0; i < 16; i++) {
                if (*ptr == '#') {
                    control++;
                }
                ptr++;
            }
            if (control != 16) {
                return 1;
            }

            ptr += check->size;
            /*if (check->next != NULL *//*&& check->next->free == 1*//*) {
                ptr += 32;
            }*/
            control = 0;
            for (int i = 0; i < 16; i++) {
                if (*ptr == '#') {
                    control++;
                }
                ptr++;
            }
            if (control != 16) {
                return 1;
            }
        }
        check = check->next;
    }
    return 0;
}
