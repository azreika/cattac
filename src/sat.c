#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "sat.h"

sat_conj_t* create_sat_conj(void) {
    sat_conj_t* ret = malloc(sizeof(sat_conj_t));
    ret->disjunctions = create_list();
    return ret;
}

sat_disj_t* create_sat_disj(void) {
    sat_disj_t* ret = malloc(sizeof(sat_disj_t));
    ret->atoms = create_list();
    return ret;
}

sat_atom_t* create_sat_atom(char* id, bool negated) {
    sat_atom_t* ret = malloc(sizeof(sat_atom_t));

    strncpy(ret->id, id, MAX_ID_LEN);
    ret->id[MAX_ID_LEN-1] = '\0';

    ret->negated = negated;

    return ret;
}

void destroy_sat_conj(sat_conj_t* conjunction) {
    linked_list* disjunctions = conjunction->disjunctions;
    for (uint64_t i = 0; i < disjunctions->size; i++) {
        destroy_sat_disj(disjunctions->elements[i]);
    }
    free(disjunctions->elements);
    free(disjunctions);
    free(conjunction);
}

void destroy_sat_disj(sat_disj_t* disjunction) {
    linked_list* atoms = disjunction->atoms;
    for (uint64_t i = 0; i < atoms->size; i++) {
        destroy_sat_atom(atoms->elements[i]);
    }
    free(atoms->elements);
    free(atoms);
    free(disjunction);
}

void destroy_sat_atom(sat_atom_t* atom) {
    free(atom);
}

void sat_add_disjunction(sat_conj_t* conjunction, sat_disj_t* disjunction) {
    list_append(conjunction->disjunctions, disjunction);
}

void sat_add_atom(sat_disj_t* disjunction, sat_atom_t* atom) {
    list_append(disjunction->atoms, atom);
}

void print_sat_conj(sat_conj_t* conjunction) {
    linked_list* disjunctions = conjunction->disjunctions;
    printf("( ");
    for (size_t i = 0; i < disjunctions->size; i++) {
        if (i != 0) {
            printf(" & ");
        }
        print_sat_disj(disjunctions->elements[i]);
    }
    printf(" )");
}

void print_sat_disj(sat_disj_t* disjunction) {
    linked_list* atoms = disjunction->atoms;
    printf("( ");
    for (size_t i = 0; i < atoms->size; i++) {
        if (i != 0) {
            printf(" | ");
        }
        print_sat_atom(atoms->elements[i]);
    }
    printf(" )");
}

void print_sat_atom(sat_atom_t* atom) {
    if (atom->negated) {
        printf("!");
    }
    printf("%s", atom->id);
}
