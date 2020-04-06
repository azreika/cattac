#ifndef CATTAC_LIST_H
#define CATTAC_LIST_H

#include <stdint.h>

#define INIT_CAP 32

typedef struct list list;

// Generic list
struct list {
    void** elements;
    uint64_t size;
    uint64_t cap;
};

/**
 * Create a new list.
 * @return empty list
 */
list* create_list(void);

/**
 * Append element to linked list.
 * @param list list to modify
 * @param element element to append
 */
void list_append(list* list, void* element);

#endif // CATTAC_LIST_H_
