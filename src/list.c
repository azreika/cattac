#include <assert.h>
#include <stdlib.h>
#include "list.h"

list* create_list() {
    list* ret = malloc(sizeof(list));

    ret->elements = malloc(sizeof(void*) * INIT_CAP);
    ret->size = 0;
    ret->cap = INIT_CAP;

    return ret;
}

void list_append(list* list, void* element) {
    assert(list->size <= list->cap && "invalid size");
    if (list->size == list->cap) {
        list->cap *= 2;
        list->elements = realloc(list->elements, sizeof(void*) * list->cap);
    }
    list->elements[list->size] = element;
    list->size++;
    return;
}
