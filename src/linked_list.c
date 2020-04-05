#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

linked_list* create_list() {
    linked_list* ret = malloc(sizeof(linked_list));

    ret->elements = malloc(sizeof(void*) * INIT_CAP);
    ret->size = 0;
    ret->cap = INIT_CAP;

    return ret;
}

void list_append(linked_list* list, void* element) {
    assert(list->size <= list->cap && "invalid size");
    if (list->size == list->cap) {
        list->cap *= 2;
        list->elements = realloc(list->elements, sizeof(void*) * list->cap);
    }
    list->elements[list->size] = element;
    list->size++;
    return;
}
