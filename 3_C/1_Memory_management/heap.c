#include "heap.h"
#include "custom_unistd.h"
#include "tested_declarations.h"
#include "rdebug.h"
#include "tested_declarations.h"
#include "rdebug.h"
#define ROUND_TO_NEXT_PAGE(__addr) (((__addr) & ~(PAGE_SIZE - 1)) + PAGE_SIZE * !!((__addr) & (PAGE_SIZE - 1)))
#define PAGE_SIZE       4096    // Długość strony w bajtach
#define PAGE_FENCE      1       // Liczba stron na jeden płotek
#define PAGES_AVAILABLE 16384   // Liczba stron dostępnych dla sterty
#define PAGES_TOTAL     (PAGES_AVAILABLE + 2 * PAGE_FENCE)

struct memory_manager_t memory_manager;
int setup_call = 0;

int heap_setup(void) {
    void *ptr = custom_sbrk(0);
    memory_manager.memory_start = ptr;
    memory_manager.memory_size = 0;
    memory_manager.first_memory_chunk = NULL;
    setup_call ++;
    return 0;
}

int control(struct memory_chunk_t*sum){
    return (int)((intptr_t)(char*)sum->prev + (intptr_t)(char*)sum->next + sum->size + sum->free);
}

void *heap_malloc(size_t size) {
    if (size > 0 && heap_validate() == 0) {
        if(memory_manager.memory_size >= size) {
            struct memory_chunk_t *memory_chunk;

            struct memory_chunk_t *curr = (struct memory_chunk_t *) memory_manager.first_memory_chunk;
            int all_ell_size = 0;
            while (curr) {
                if(curr->free == 1){
                    all_ell_size += (int) curr->size + (int) sizeof(struct memory_chunk_t) ;
                }
                else {
                    all_ell_size += (int) curr->size + (int) sizeof(struct memory_chunk_t) + 32;
                }
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
                memory_chunk->control_sum = (int)size + 0;
                ptr = (char *) memory_chunk + sizeof(struct memory_chunk_t) + size + 16;
                for (int i = 0; i < 16; i++) {
                    *ptr = '#';
                    ptr++;
                }
                heap_validate();
                return  ptr - 16 - memory_chunk->size;
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
                    curr->control_sum = (int)((intptr_t)(char*)curr->next + (intptr_t)(char*)curr->prev + size + 0);
                    ptr += size;
                    for (int i = 0; i < 16; i++) {
                        *ptr = '#';
                        ptr++;
                    }
                    heap_validate();
                    return  ptr - 16 - size;
                }/* else if (curr->next == NULL && (int) (memory_manager.memory_size - all_ell_size) >= (int) (size + 32 + sizeof(struct memory_chunk_t))) {
                    if((char*)custom_sbrk(0) - 32 - size - sizeof(struct  memory_chunk_t) >=(char*)curr + 32 + sizeof(struct memory_chunk_t) + curr->size) {
                        char *next = (char *) curr;
                        if (curr->free != 1) {
                            next = next + curr->size + sizeof(struct memory_chunk_t) + 32;
                        } else {
                            next = next + curr->size + sizeof(struct memory_chunk_t);
                        }
                        curr->next = (struct memory_chunk_t *) (next);
                        char *ptr = (char *) curr->next + sizeof(struct memory_chunk_t);
                        for (int i = 0; i < 16; i++) {
                            *ptr = '#';
                            ptr++;
                        }
                        curr->next->prev = curr;
                        curr->control_sum = control(curr);
                        curr->next->next = NULL;
                        curr->next->size = size;
                        curr->next->free = 0;
                        curr->next->control_sum = control(curr->next);
                        ptr += size;
                        for (int i = 0; i < 16; i++) {
                            *ptr = '#';
                            ptr++;
                        }
                        heap_validate();
                        return ptr - 16 - size;
                    }
                }*/

                curr = curr->next;
            }
            goto add_size;
        }
        else {
            add_size:;
            struct memory_chunk_t *new_block = custom_sbrk(0);
            void *add = custom_sbrk((intptr_t) (size + 32 + sizeof(struct memory_chunk_t)));
            if (add != (void *) -1) {

                //memory_manager.memory_start = (char*)add - memory_manager.memory_size;
                memory_manager.memory_size += (size + 32 + sizeof(struct memory_chunk_t));

                struct memory_chunk_t *last = memory_manager.first_memory_chunk;
                if(last != NULL) {
                    while(last->next){
                        last = last->next;
                    }
                    last->next = new_block;
                    last->control_sum = control(last);
                }
                else{
                    memory_manager.first_memory_chunk = new_block;
                }

                new_block->prev = last;
                new_block->next = NULL;
                new_block->size = size;
                new_block->free = 0;
                new_block->control_sum = control(new_block);
                char*ptr = (char*)new_block + sizeof(struct memory_chunk_t);
                for(int i = 0; i < 16; i++){
                    *ptr = '#';
                    ptr++;
                }
                ptr += size;
                for(int i = 0; i < 16; i++){
                    *ptr = '#';
                    ptr++;
                }
                heap_validate();
                return ptr - size - 16;
            }
            else {
                return NULL;
            }

        }

    }

    return NULL;

}

void heap_clean(void) {
    uint64_t whole_struct_size = custom_sbrk_get_reserved_memory();
    custom_sbrk(-1*(intptr_t)whole_struct_size);

    setup_call --;
    if(setup_call < 0){
        setup_call = 0;
    }

}

void heap_free(void *memblock) {
    void *address = memblock;
    if (address != NULL) {
        address = (void *) ((char *) address - (char *) 0x30);
        if (memory_manager.memory_start <= address && (char*) address <=
                                                      (char *) custom_sbrk(0) && heap_validate() == 0) {
            struct memory_chunk_t *block_to_free = (struct memory_chunk_t *) address;
            bool good = 0;
            struct memory_chunk_t *curr = memory_manager.first_memory_chunk;
            while (curr != NULL) {
                if (curr == block_to_free) {
                    if(curr->free != 1) {
                        good = 1;
                        break;
                    }
                }
                curr = curr->next;
            }
            if (good == 1) {
                if (block_to_free->next == NULL && block_to_free->prev == NULL) {

                    char *ptr = (char *) block_to_free + sizeof(struct memory_chunk_t);
                    for (int i = 0; i < 16; i++) {
                        if (*ptr == '#') {
                            *ptr = '0';
                        }
                        ptr++;
                    }
                    ptr += block_to_free->size;
                    for (int i = 0; i < 16; i++) {
                        if (*ptr == '#') {
                            *ptr = '0';
                        }
                        ptr++;
                    }
                    heap_clean();
                    heap_setup();
                    memblock = NULL;
                    return;
                } else if (block_to_free->next == NULL) {
                    if (block_to_free->prev->free == 1) {

                            //memory_init(memory_manager.memory_start, memory_manager.memory_size);
                            char *ptr = (char *) block_to_free + sizeof(struct memory_chunk_t);
                            for (int i = 0; i < 16; i++) {
                                if (*ptr == '#') {
                                    *ptr = '0';
                                }
                                ptr++;
                            }
                            ptr += block_to_free->size;
                            for (int i = 0; i < 16; i++) {
                                if (*ptr == '#') {
                                    *ptr = '0';
                                }
                                ptr++;
                            }


                            block_to_free->prev->size = (size_t)((char*) custom_sbrk(0) - ((char*)block_to_free->prev + sizeof(struct memory_chunk_t)));
                            block_to_free->prev->next = NULL;
                            block_to_free->prev->control_sum = control(block_to_free->prev);
                            return;

                    } else {
                        block_to_free->free = 1;
                        block_to_free->size += 32;
                        char *ptr = (char *) block_to_free + sizeof(struct memory_chunk_t);
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        ptr += block_to_free->size - 32;
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        block_to_free->control_sum = control(block_to_free);

                    }
                } else if (block_to_free->prev == NULL) {
                    block_to_free->free = 1;
                    if(block_to_free->next->free == 1){
                        char *ptr = (char *) block_to_free + sizeof(struct memory_chunk_t);
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        ptr += block_to_free->size;
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        block_to_free->size = (size_t)((char*)block_to_free->next->next - ((char*)block_to_free + sizeof(struct memory_chunk_t)));
                        block_to_free->next = block_to_free->next->next;
                        block_to_free->control_sum = control(block_to_free);
                        if(block_to_free->next != NULL) {
                            block_to_free->next->prev = block_to_free;
                            block_to_free->next->control_sum = control(block_to_free->next);
                        }
                        return;
                    }
                    char *ptr = (char *) block_to_free + sizeof(struct memory_chunk_t);
                    for (int i = 0; i < 16; i++) {
                        if (*ptr == '#') {
                            *ptr = '0';
                        }
                        ptr++;
                    }
                    ptr += block_to_free->size;
                    for (int i = 0; i < 16; i++) {
                        if (*ptr == '#') {
                            *ptr = '0';
                        }
                        ptr++;
                    }
                    size_t free = (char*)block_to_free->next - ptr;
                    block_to_free->size += 32 + free;
                    block_to_free->free = 1;
                    block_to_free->control_sum = control(block_to_free);
                    return;
                } else {
                    if(block_to_free->prev->free == 1 && block_to_free->next->free == 1){
                        char *ptr = (char *) block_to_free + sizeof(struct memory_chunk_t);
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        ptr += block_to_free->size;
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        size_t three_struct_size = 0;
                        if(block_to_free->next->next == NULL){
                            three_struct_size = (size_t)((char*) custom_sbrk(0) - ((char*)block_to_free->prev + sizeof(struct memory_chunk_t)));
                            block_to_free->prev->next = NULL;
                        }
                        else{
                            three_struct_size = (size_t)((char*)block_to_free->next->next - ((char*)block_to_free->prev + sizeof(struct memory_chunk_t)));
                            block_to_free->prev->next = block_to_free->next->next;
                            block_to_free->prev->next->prev = block_to_free->prev;
                            block_to_free->prev->next->control_sum = control(block_to_free->prev->next);
                        }
                        block_to_free = block_to_free->prev;
                        block_to_free->size =three_struct_size;
                        block_to_free->control_sum = control(block_to_free);
                        return;
                    }
                    else if(block_to_free->prev->free == 1){
                        char *ptr = (char *) block_to_free + sizeof(struct memory_chunk_t);
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        ptr += block_to_free->size;
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }


                        block_to_free->prev->size = (size_t)((char*) custom_sbrk(0) - ((char*)block_to_free->prev + sizeof(struct memory_chunk_t)));
                        block_to_free->prev->next = NULL;
                        block_to_free->prev->control_sum = control(block_to_free->prev);
                        return;
                    }
                    else if(block_to_free->next->free == 1){
                        char *ptr = (char *) block_to_free + sizeof(struct memory_chunk_t);
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        ptr += block_to_free->size;
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        block_to_free->size = (size_t)((char*)block_to_free->next->next - ((char*)block_to_free + sizeof(struct memory_chunk_t)));
                        block_to_free->next = block_to_free->next->next;
                        block_to_free->free = 1;
                        block_to_free->control_sum = control(block_to_free);
                        if(block_to_free->next != NULL) {
                            block_to_free->next->prev = block_to_free;
                            block_to_free->next->control_sum = control(block_to_free->next);
                        }
                        return;
                    }
                    else{
                        char *ptr = (char *) block_to_free + sizeof(struct memory_chunk_t);
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        ptr += block_to_free->size;
                        for (int i = 0; i < 16; i++) {
                            if (*ptr == '#') {
                                *ptr = '0';
                            }
                            ptr++;
                        }
                        size_t free = (char*)block_to_free->next - ptr;
                        block_to_free->size += 32 + free;
                        block_to_free->free = 1;
                        block_to_free->control_sum = control(block_to_free);
                        return;
                    }



                }

            }
        }
    }
}

int heap_validate(void) {
    struct memory_chunk_t *check = (struct memory_chunk_t *) memory_manager.first_memory_chunk;
    if(setup_call == 0){
        return 2;
    }



    while (check) {
        if (check->free != 1) {
            if(check->free != 0){
                return 3;
            }
            if(check->prev != NULL) {
                if (check != check->prev->next ) {
                    return 3;
                }
            }

            if(check->control_sum != (int)((intptr_t)(char*)check->prev + (intptr_t)(char*)check->next + check->size + check->free)){
                return 3;
            }
            if(check->prev != NULL && (int)((intptr_t)(char*)check->prev) == 0){
                return 3;
            }
            if(check->next != NULL && (int)(intptr_t)(char*)check->next == 0){
                return 3;
            }

            char *ptr = (char *) check + sizeof(struct memory_chunk_t) + 32 + check->size;
            if(ptr == NULL){
                return 3;
            }
            if(check->next != NULL) {
                long free_space_ptr = (char*)check->next - ptr;

                if (check->size !=
                    (size_t) ((char *) (check->next) - (char *) (check) - 32 - sizeof(struct memory_chunk_t) - free_space_ptr) && *(ptr-1) == '#') {
                    return 3;
                }
                if (check != check->next->prev ) {
                    return 3;
                }

            }
            else{
                if (check->size !=
                    (size_t) (ptr - (char *) (check) - 32 - sizeof(struct memory_chunk_t) ) && *(ptr-1) == '#') {
                    return 3;
                }
            }

            if(check->size > custom_sbrk_get_reserved_memory()){
                return 3;
            }
            ptr = (char *) check + sizeof(struct memory_chunk_t);
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
    check = (struct memory_chunk_t *) memory_manager.first_memory_chunk;
    if(check != NULL) {
        while (check->next) {
            check = check->next;
        }
        if (check->free == 0 && (void *) ((char*)check + check->size + sizeof(struct memory_chunk_t) + 32) > custom_sbrk(0)) {
            custom_sbrk(0);
            return 3;
        } else if ((void *) ((char*)check + check->size + sizeof(struct memory_chunk_t)) > custom_sbrk(0)) {
            custom_sbrk(0);
            return 3;
        }
    }

    return 0;
}

enum pointer_type_t get_pointer_type(const void *const pointer) {
    if (pointer == NULL) {
        return pointer_null;
    } else if (heap_validate() != 0) {
        return pointer_heap_corrupted;
    }
    struct memory_chunk_t *test =  memory_manager.first_memory_chunk;

    while (test) {
        char *ptr = (char *) test + sizeof(struct memory_chunk_t) + 16;
        if ((ptr - sizeof(struct memory_chunk_t) - 16) <=  (char*)pointer && ptr - 16 > (char*)pointer) {
            if(test->free == 1){
                return pointer_unallocated;
            }
            return pointer_control_block;
        } else if ((pointer >= (const void*)(ptr - 16) && pointer < (const void*)ptr) || (pointer >= (const void*)(ptr + test->size) && pointer < (const void*)(ptr + test->size + 16))) {
            if(test->free == 1){
                return pointer_unallocated;
            }
            return pointer_inside_fences;
        }else if ( (char*)pointer == ptr) {
            if(test->free == 1){
                return pointer_unallocated;
            }
            return pointer_valid;
        }else if ( (char*)pointer > ptr &&  (char*)pointer < ptr + test->size) {
            if(test->free == 1){
                return pointer_unallocated;
            }
            return pointer_inside_data_block;
        }
        test = test->next;
    }

    return pointer_unallocated;


}

void *heap_calloc(size_t number, size_t size) {
    if (number > 0 && size > 0 ) {
        void *address = heap_malloc((number * size));
        if (address == NULL) {
            return NULL;
        }
        memset(address, 0, (number * size));
        return address;
    }
    return NULL;
}



void *heap_realloc(void *memblock, size_t size) {
    if(heap_validate() != 0){
        return NULL;
    }
    if(memblock == NULL){
        void *temp = heap_malloc(size);
        if(temp == NULL){
            heap_validate();
            return NULL;
        }
        memblock = temp;
        heap_validate();
        return memblock;
    }
    void *address = memblock;
    address = (void *) ((char *) address - (char *) 0x30);
    if (memory_manager.memory_start <= address && (struct memory_manager_t *) address <=
                                                  (struct memory_manager_t *) (char *) memory_manager.memory_start +
                                                  memory_manager.memory_size && heap_validate() == 0) {
        struct memory_chunk_t* realloc = (struct memory_chunk_t*)address;
        bool good = 0;
        struct memory_chunk_t *curr = memory_manager.first_memory_chunk;
        while (curr != NULL) {
            if (curr == realloc) {
                if(curr->free != 1) {
                    good = 1;
                    break;
                }
            }
            curr = curr->next;
        }


    if(good == 1) {
        if (size < realloc->size) {
            if (size == 0) {
                heap_free(memblock);
                memblock = NULL;
                return memblock;
            }
            char *ptr = (char *) realloc + sizeof(struct memory_chunk_t) + 16 + realloc->size;
            for (int i = 0; i < 16; i++) {
                *ptr = '0';
                ptr++;
            }
            ptr = (char *) realloc + sizeof(struct memory_chunk_t) + 16 + size;
            for (int i = 0; i < 16; i++) {
                *ptr = '#';
                ptr++;
            }
            realloc->size = size;
            realloc->control_sum = control(realloc);
            heap_validate();

            return memblock;
        } else if (size == realloc->size) {
            heap_validate();

            return memblock;
        } else {
            size_t free_space = 0;
            if (realloc->next != NULL) {
                char *free_ptr;
                if (realloc->free == 0) {
                    free_ptr = (char *) realloc + realloc->size + sizeof(struct memory_chunk_t) + 32;
                } else {
                    free_ptr = (char *) realloc + realloc->size + sizeof(struct memory_chunk_t);
                }
                while ((struct memory_chunk_t *) free_ptr != realloc->next) {
                    free_space++;
                    free_ptr++;
                }

            }
            if (realloc->size + free_space >= size) {
                char *ptr = (char *) realloc + sizeof(struct memory_chunk_t) + 16 + realloc->size;
                for (int i = 0; i < 16; i++) {
                    *ptr = '0';
                    ptr++;
                }
                ptr = (char *) realloc + sizeof(struct memory_chunk_t) + 16 + size;
                for (int i = 0; i < 16; i++) {
                    *ptr = '#';
                    ptr++;
                }
                realloc->size = size;
                realloc->control_sum = control(realloc);
                heap_validate();

                return memblock;
            }
            if (realloc->next != NULL && realloc->next->free == 1 &&
                realloc->size + free_space + realloc->next->size >= size) {
                size_t mem_from_next = size - realloc->size - free_space;
                char *ptr_dst = (char *) realloc->next  + mem_from_next;
                char *ptr_src = (char *) realloc->next;
                memmove(ptr_dst, ptr_src, sizeof(struct memory_chunk_t));
                realloc->next = (struct memory_chunk_t *) ptr_dst;
                realloc->size = size;
                char *ptr = (char*)realloc + sizeof(struct memory_chunk_t) + 16 + size;
                for(int i = 0; i < 16; i++){
                    *ptr = '#';
                    ptr++;
                }
                realloc->control_sum = control(realloc);

                realloc->next->size -= mem_from_next;
                realloc->next->control_sum = control(realloc->next);

                if (realloc->next->next != NULL) {
                    realloc->next->next->prev = realloc->next;
                    realloc->next->next->control_sum = control(realloc->next->next);
                }
                heap_validate();

                return memblock;
            }
            if (realloc->next == NULL) {
                size_t needed_mem = size - realloc->size;
                void *add = custom_sbrk((intptr_t) needed_mem);
                if (add == (void *) -1) {
                    heap_validate();
                    return NULL;
                }
                memory_manager.memory_start = (char *) add - memory_manager.memory_size;
                memory_manager.memory_size += needed_mem;
                if (realloc->free == 0) {
                    char *ptr_dest = (char *) realloc + sizeof(struct memory_chunk_t) + 16 + size;
                    char *ptr_src = (char *) realloc + sizeof(struct memory_chunk_t) + 16 + realloc->size;
                    memset(ptr_src, '0', 16);
                    memset(ptr_dest, '#', 16);

                }
                realloc->size = size;
                realloc->control_sum = control(realloc);
                heap_validate();

                return memblock;
            }
            void *new = heap_malloc(size);

            if (new == NULL) {
                return NULL;
            }
            memcpy(new, memblock, realloc->size);
            heap_free(memblock);
            return new;
        }
    }
    }

    heap_validate();

    return NULL;
}



size_t heap_get_largest_used_block_size(void) {
    struct memory_chunk_t *first = memory_manager.first_memory_chunk;
    if (first == NULL) {
        return 0;
    } else if (heap_validate() != 0) {
        return 0;
    }
    size_t max = 0;
    while (first) {
        if (first->size > max && first->free == 0) {
            max = first->size;
        }
        first = first->next;
    }
    return max;
}

void *heap_malloc_aligned(size_t count) {
    if(count > 0) {
        if(memory_manager.first_memory_chunk == NULL){
            void *free_page = custom_sbrk(PAGE_SIZE - sizeof(struct memory_chunk_t) - 16);
            if(free_page == (void*)-1){

                return NULL;
            }

            memory_manager.memory_start = (char*)free_page + (PAGE_SIZE - sizeof(struct memory_chunk_t) - 16);

            void*new = custom_sbrk((intptr_t)(count + 32 + sizeof(struct memory_chunk_t)));

            if(new != (void*)-1){
                struct memory_chunk_t *new_aligned = memory_manager.memory_start;
                memory_manager.first_memory_chunk = new_aligned;
                memory_manager.memory_size += count + 32 + sizeof(struct memory_chunk_t);

                new_aligned->prev = NULL;
                new_aligned->next = NULL;
                new_aligned->size = count;
                new_aligned->free = 0;
                new_aligned->control_sum = control(new_aligned);

                char *ptr = (char*)new_aligned + sizeof(struct memory_chunk_t);
                for(int i = 0; i < 16; i++){
                    *ptr = '#';
                    ptr++;
                }
                ptr += count;
                for(int i = 0; i < 16; i++){
                    *ptr = '#';
                    ptr++;
                }
                char *temp = ptr - count - 16;
                heap_validate();
                if(((intptr_t)temp & (intptr_t)(PAGE_SIZE - 1)) == 0) {
                    return temp;
                }
                else{
                    return NULL;
                }
            }
            else{
                return NULL;
            }

        }
        struct memory_chunk_t *free_block = memory_manager.first_memory_chunk;
        while (free_block){
            if(free_block->free == 1){
                if(free_block->next != NULL) {
                    if (free_block->size >= count + 32) {
                        char *ptr = (char *) free_block;
                        if (ROUND_TO_NEXT_PAGE((intptr_t) ptr) - (intptr_t) ptr == 16 + sizeof(struct memory_chunk_t)) {
                            ptr += sizeof(struct memory_chunk_t);
                            for (int i = 0; i < 16; i++) {
                                *ptr = '#';
                                ptr++;
                            }
                            ptr += count;
                            for (int i = 0; i < 16; i++) {
                                *ptr = '#';
                                ptr++;
                            }
                            if (count - free_block->size > 0) {
                                memory_manager.memory_size += count - free_block->size;
                            }
                            free_block->free = 0;
                            free_block->size = count;
                            free_block->control_sum = control(free_block);
                            char *temp = ptr - count - 16;
                            heap_validate();

                            if (((intptr_t) temp & (intptr_t) (PAGE_SIZE - 1)) == 0) {
                                return temp;
                            } else {
                                return NULL;
                            }
                        }
                    }

                    if (free_block->next->free == 1 &&
                        (char *) free_block->next + sizeof(struct memory_chunk_t) + free_block->next->size -
                        (char *) free_block -
                        sizeof(struct memory_chunk_t) >= count + 32) {
                        char *ptr = (char *) free_block + sizeof(struct memory_chunk_t) + free_block->size + 16;
                        for (int i = 0; i < 16; i++) {
                            *ptr = '0';
                            ptr++;
                        }
                        char *dst = (char *) free_block + sizeof(struct memory_chunk_t) + count + 32;
                        char *src = (char *) free_block->next;
                        memmove(dst, src, sizeof(struct memory_chunk_t));
                        free_block->size = count;
                        ptr = (char *) free_block + sizeof(struct memory_chunk_t) + free_block->size + 16;
                        for (int i = 0; i < 16; i++) {
                            *ptr = '#';
                            ptr++;
                        }
                        free_block->next = (struct memory_chunk_t *) dst;
                        free_block->free = 0;
                        free_block->control_sum = control(free_block);

                        free_block->next->next->prev = (struct memory_chunk_t *) dst;
                        free_block->next->free = 0;
                        free_block->next->control_sum = control(free_block->next);
                        return ptr - count - 16;
                    }
                }
            }
            free_block = free_block->next;
        }

        char *ptr = (char*) custom_sbrk(0);


        size_t to_next_page = ROUND_TO_NEXT_PAGE((intptr_t)ptr) - (intptr_t)ptr;
        if(to_next_page == (sizeof(struct memory_chunk_t) + 16)){
            char*temp = heap_malloc(count);
            heap_validate();

            if(((intptr_t)temp & (intptr_t)(PAGE_SIZE - 1)) == 0) {
                return temp;
            }
            else{
                return NULL;
            }
        }
        else if(to_next_page > (intptr_t)(sizeof(struct memory_chunk_t) + 16)) {
            void *difference = custom_sbrk((intptr_t)(to_next_page -  ((sizeof(struct memory_chunk_t) + 16))));
            if(difference == (void *)-1){
                return NULL;
            }
            //memory_manager.memory_size += ROUND_TO_NEXT_PAGE((intptr_t) ptr) - ptr_cpy - (intptr_t) (sizeof(struct memory_chunk_t) + 16);
            char*temp = heap_malloc(count);
            heap_validate();

            if(((intptr_t)temp & (intptr_t)(PAGE_SIZE - 1)) == 0) {
                return temp;
            }
            else{
                return NULL;
            }
        }
        else{
            void *new_page_difference = custom_sbrk(PAGE_SIZE - sizeof(struct memory_chunk_t) - 16 + to_next_page);
            if(new_page_difference == (void *)-1){
                return NULL;
            }
            //memory_manager.memory_size += ROUND_TO_NEXT_PAGE((intptr_t) ptr) - ptr_cpy;
            char*temp = heap_malloc(count);
            heap_validate();

            if(((intptr_t)temp & (intptr_t)(PAGE_SIZE - 1)) == 0) {
                return temp;
            }
            else{
                return NULL;
            }
        }
    }
    heap_clean();
    heap_setup();
    return NULL;
}

void *heap_calloc_aligned(size_t number, size_t size) {
    if (number > 0 && size > 0 && (unsigned long int)(number * size ) <= (unsigned long int)(PAGE_SIZE * PAGES_AVAILABLE + PAGE_FENCE * PAGES_AVAILABLE) - (unsigned long int)((char*)custom_sbrk(0) - (char*)memory_manager.memory_start) ) {
        void *address = heap_malloc_aligned((number * size));
        if (address == NULL) {
            return NULL;
        }
        memset(address, 0, (number * size));
        return address;
    }
    return NULL;
}

void *heap_realloc_aligned(void *memblock, size_t size) {
    if(setup_call > 0) {
        if(heap_validate() != 0){
            return NULL;
        }
        if (!memblock) {
            return heap_malloc_aligned(size);
        }


        void *address = memblock;
        address = (void *) ((char *) address - (char *) 0x30);
        if (memory_manager.memory_start <= address && (struct memory_manager_t *) address <=
                                                      (struct memory_manager_t *) custom_sbrk(0)) {
            struct memory_chunk_t *realloc = (struct memory_chunk_t *) address;
            if(size == 0){
                heap_free(memblock);
                if((realloc->prev == NULL && realloc->next == NULL) || memory_manager.first_memory_chunk == NULL) {
                    memblock = NULL;
                }

                return memblock;
            }
            char *round_ptr;
            if(realloc->free == 1){
                round_ptr = (char*)realloc + sizeof(struct memory_chunk_t) + realloc->size;
            }
            else {
                round_ptr = (char *) realloc + sizeof(struct memory_chunk_t) + 32 + realloc->size;
            }
            size_t round = ROUND_TO_NEXT_PAGE((intptr_t)round_ptr) - (intptr_t)round_ptr;
            if(realloc->control_sum == control(realloc)) {
                if (realloc->size + round >= size) {
                    int diff = (int)(size - realloc->size);
                    if(diff > 0){
                        void *add = custom_sbrk((intptr_t)diff);
                        if(add == (void*)-1){
                            return NULL;
                        }
                    }
                    quick_realloc:;
                    char *ptr = (char *) realloc + sizeof(struct memory_chunk_t) + 16 + realloc->size;
                    for (int i = 0; i < 16; i++) {
                        *ptr = '0';
                        ptr++;
                    }
                    realloc->size = size;
                    realloc->control_sum = control(realloc);
                    ptr = (char *) realloc + sizeof(struct memory_chunk_t) + 16 + realloc->size;
                    for (int i = 0; i < 16; i++) {
                        *ptr = '#';
                        ptr++;
                    }
                    return memblock;
                }
                size_t count = realloc->size;
                if(realloc->next == NULL){
                    void *add = custom_sbrk((intptr_t)(size - count));
                    if(add == (void*)-1){
                        return NULL;
                    }
                    memory_manager.memory_size += size - count;
                    realloc->size = size;
                    goto quick_realloc;

                }
                else if(realloc->next->free == 1){
                    if(realloc->free == 1 && (char*)realloc->next + sizeof(struct memory_chunk_t) + realloc->next->size - (char*)realloc - sizeof(struct memory_chunk_t)  >= size + 32) {

                        return heap_malloc_aligned(size);
                    }
                    else if((char*)realloc->next + sizeof(struct memory_chunk_t) + realloc->next->size - (char*)realloc - sizeof(struct memory_chunk_t)  >= size ){
                        heap_free(memblock);
                        return heap_malloc_aligned(size);
                    }
                }
                void *ptr = heap_malloc_aligned(size);
                if (!ptr) {
                    return NULL;
                }
                memcpy(ptr, memblock, count);
                heap_free(memblock);
                return ptr;
            }
        }
    }
    return NULL;
}


