#ifndef CATTAC_LINKED_LIST_H
#define CATTAC_LINKED_LIST_H

#include <stdint.h>

#define INIT_CAP 32

typedef struct linked_list linked_list;

// Generic linked list
struct linked_list {
    void** elements;
    uint64_t size;
    uint64_t cap;
};

/**
 * Create a new linked list.
 * @return empty linked list
 */
linked_list* create_list(void);

/**
 * Append element to linked list.
 * @param list list to modify
 * @param element element to append
 */
void list_append(linked_list* list, void* element);

#endif // CATTAC_LINKED_LIST_H
