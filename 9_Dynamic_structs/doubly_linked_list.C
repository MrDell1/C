#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"
struct doubly_linked_list_t *dll_create() {
    struct doubly_linked_list_t *dll;
    dll = (struct doubly_linked_list_t *) calloc(1, sizeof(struct doubly_linked_list_t));
    if (dll == NULL) {
        return NULL;
    }
    dll->head = NULL;
    dll->tail = NULL;
    return dll;
}

int dll_push_back(struct doubly_linked_list_t *dll, int value) {
    if (dll == NULL) {
        return 1;
    }
    if (dll->tail == NULL) {
        dll->tail = (struct node_t *) calloc(1, sizeof(struct node_t));
        if (dll->tail == NULL) {
            return 2;
        }
        dll->tail->data = value;
        dll->head = dll->tail;
        dll->tail->next = NULL;
        dll->tail->prev = NULL;
        return 0;
    } else {
        struct node_t *new = ((struct node_t *) calloc(1, sizeof(struct node_t)));
        if (new == NULL) {
            return 2;
        }
        struct node_t *last = dll->head;

        new->data = value;
        new->next = NULL;

        while (last->next != NULL) {
            last = last->next;
        }

        last->next = new;
        new->prev = last;
        dll->tail = new;
    }
    return 0;
}

int dll_push_front(struct doubly_linked_list_t *dll, int value) {
    if (dll == NULL) {
        return 1;
    }
    if (dll->head == NULL) {
        dll->head = (struct node_t *) calloc(1, sizeof(struct node_t));
        if (dll->head == NULL) {
            return 2;
        }
        dll->head->data = value;
        dll->tail = dll->head;
        dll->head->next = NULL;
        dll->head->prev = NULL;
        return 0;
    } else {
        struct node_t *new = ((struct node_t *) calloc(1, sizeof(struct node_t)));
        if (new == NULL) {
            return 2;
        }
        new->data = value;
        new->prev = NULL;
        struct node_t *old_head = dll->head;
        dll->head->prev = new;
        new->next = old_head;
        dll->head = new;
    }
    return 0;

}

int dll_pop_front(struct doubly_linked_list_t *dll, int *err_code) {
    if (dll == NULL || dll->head == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return 1;
    }

    struct node_t *temp = dll->head;
    int pop_front = dll->head->data;
    if (dll->head->next == NULL) {
        free(temp);
        dll->tail = NULL;
        dll->head = NULL;
        if (err_code != NULL) {
            *err_code = 0;
        }
        return pop_front;
    }
    dll->head = dll->head->next;
    dll->head->prev = NULL;
    free(temp);
    if (err_code != NULL) {
        *err_code = 0;
    }
    return pop_front;
}

int dll_pop_back(struct doubly_linked_list_t *dll, int *err_code) {
    if (dll == NULL || dll->tail == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return 1;
    }


    struct node_t *temp = dll->tail;
    int pop_front = dll->tail->data;
    if (dll->tail->prev == NULL) {
        free(temp);
        dll->tail = NULL;
        dll->head = NULL;
        if (err_code != NULL) {
            *err_code = 0;
        }
        return pop_front;
    }
    dll->tail = dll->tail->prev;
    dll->tail->next = NULL;
    free(temp);
    if (err_code != NULL) {
        *err_code = 0;
    }
    return pop_front;
}

int dll_back(const struct doubly_linked_list_t *dll, int *err_code) {
    if (dll == NULL || dll->tail == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }

        return 1;
    }

    int dll_back = dll->tail->data;
    if (err_code != NULL) {
        *err_code = 0;
    }
    return dll_back;

}

int dll_front(const struct doubly_linked_list_t *dll, int *err_code) {
    if (dll == NULL || dll->head == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return 1;
    }

    int dll_back = dll->head->data;
    if (err_code != NULL) {
        *err_code = 0;
    }
    return dll_back;
}

struct node_t *dll_begin(struct doubly_linked_list_t *dll) {
    if (dll == NULL || dll->head == NULL) {
        return NULL;
    }
    return dll->head;
}

struct node_t *dll_end(struct doubly_linked_list_t *dll) {
    if (dll == NULL || dll->tail == NULL) {
        return NULL;
    }
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t *dll) {
    if (dll == NULL) {
        return -1;
    }
    int i = 0;
    struct node_t *curr = dll->head;
    while (curr != NULL) {
        i++;
        curr = curr->next;
    }
    return i;
}

int dll_is_empty(const struct doubly_linked_list_t *dll) {
    if (dll == NULL) {
        return -1;
    }
    int x = dll_size(dll);
    if (x == 0) {
        return 1;
    } else if (x > 0) {
        return 0;
    } else {
        return -1;
    }

}

int dll_at(const struct doubly_linked_list_t *dll, unsigned int index, int *err_code) {
    if (dll == NULL || (int) index >= dll_size(dll) || (int) index < 0) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return 1;
    }
    struct node_t *at = dll->head;
    for (int i = 0; i < (int) index; i++) {
        at = at->next;
        if (at == NULL) {
            if (err_code != NULL) {
                *err_code = 1;
            }
            return 1;
        }
    }
    if (err_code != NULL) {
        *err_code = 0;
    }
    return at->data;
}

int dll_insert(struct doubly_linked_list_t *dll, unsigned int index, int value) {
    if (dll == NULL || (int) index > dll_size(dll) || (int) index < 0) {
        return 1;
    }
    if ((int) index == 0) {
        int err = dll_push_front(dll, value);
        if (err == 0) {
            return 0;
        } else if (err == 1) {
            return 1;
        } else {
            return 2;
        }
    } else if ((int) index == dll_size(dll)) {
        int err = dll_push_back(dll, value);
        if (err == 0) {
            return 0;
        } else if (err == 1) {
            return 1;
        } else {
            return 2;
        }
    } else {
        struct node_t *at = dll->head;
        for (int i = 1; i < (int) index; i++) {
            at = at->next;
        }
        if (at == NULL) {
            dll_push_back(dll, value);
            return 0;
        }
        struct node_t *new = ((struct node_t *) calloc(1, sizeof(struct node_t)));
        if (new == NULL) {
            return 2;
        }
        new->data = value;
        new->next = at->next;
        at->next = new;
        new->prev = at;
        if (new->next != NULL) {
            new->next->prev = new;
        }
    }

    return 0;
}

int dll_remove(struct doubly_linked_list_t *dll, unsigned int index, int *err_code) {
    if (dll != NULL && (int) index >= 0) {

        struct node_t *at = dll->head;
        for (int i = 0; i < (int) index; i++) {
            at = at->next;
            if (at == NULL) {
                if (err_code != NULL) {
                    *err_code = 1;
                }
                return 1;
            }
        }
        if (at == NULL) {
            if (err_code != NULL) {
                *err_code = 1;
            }
            return 1;
        }

        int value = at->data;
        if (at == dll->head) {
            dll->head = at->next;
        }
        if (at->next != NULL) {
            at->next->prev = at->prev;
        }
        if (at->prev != NULL) {
            at->prev->next = at->next;
        }
        if (at->next == NULL) {
            dll->tail = at->prev;
        }
        free(at);
        if (err_code != NULL) {
            *err_code = 0;
        }
        return value;

    }

    if (err_code != NULL) {
        *err_code = 1;
    }
    return 1;
}

void dll_clear(struct doubly_linked_list_t *dll) {
    if (dll != NULL && dll->head != NULL) {
        struct node_t *current = dll->head;
        struct node_t *next;

        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
        dll->head = NULL;
        dll->tail = NULL;
        //free(dll);
        // dll = NULL;
    } else if (dll != NULL && dll->head == NULL) {
        //free(dll);
        //dll = NULL;
    } else {

    }
}

void dll_display(const struct doubly_linked_list_t *dll) {
    if (dll != NULL && dll->head != NULL && dll_size(dll) > 0) {
        struct node_t *at = dll->head;
        for (int i = 0; i < dll_size(dll); i++) {
            printf("%d ", at->data);
            at = at->next;
        }
        printf("\n");
    }

}

void dll_display_reverse(const struct doubly_linked_list_t *dll) {
    if (dll != NULL && dll->tail != NULL && dll_size(dll) > 0) {
        struct node_t *at = dll->tail;
        for (int i = dll_size(dll); i > 0; i--) {
            printf("%d ", at->data);
            at = at->prev;
        }
        printf("\n");
    }
}
