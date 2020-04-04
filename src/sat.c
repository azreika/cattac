#include "sat.h"

sat_conj_t* create_sat_conj(void) {
    sat_conj_t* ret = malloc(sizeof(sat_conj_t));

    ret->disjunctions = malloc(sizeof(sat_disj_t) * INIT_CAP);
    ret->size = 0;
    ret->cap = INIT_CAP;

    return ret;
}

sat_disj_t* create_sat_disj(void) {
    sat_disj_t* ret = malloc(sizeof(sat_disj_t));

    ret->atoms = malloc(sizeof(sat_atom_t) * INIT_CAP);
    ret->size = 0;
    ret->cap = INIT_CAP;

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
    for (uint64_t i = 0; i < conjunction->size; i++) {
        destroy_sat_disj(conjunction->disjunctions[i]);
    }
    free(conjunction);
}

void destroy_sat_disj(sat_disj_t* disjunction) {
    for (uint64_t i = 0; i < disjunction->size; i++) {
        destroy_sat_atom(disjunction->atoms[i]);
    }
    free(disjunction);
}

void destroy_sat_atom(sat_atom_t* atom) {
    free(atom);
}

void sat_add_disjunction(sat_conj_t* conjunction, sat_disj_t* disjunction) {
    assert(conjunction->size <= conjunction->cap && "invalid size");
    if (conjunction->size == conjunction->cap) {
        conjunction->cap *= 2;
        conjunction->disjunctions = realloc(sizeof(sat_disj_t) * conjunction->cap);
    }
    conjunction->disjunctions[size] = disjunction;
    conjunction->size += 1;
    return;
}

void sat_add_atom(sat_disj_t* disjunction, sat_atom_t* atom) {
    assert(disjunction->size <= disjunction->cap && "invalid size");
    if (disjunction->size == disjunction->cap) {
        disjunction->cap *= 2;
        disjunction->atoms = realloc(sizeof(sat_atom_t) * disjunction->cap);
    }
    disjunction->atoms[size] = atom;
    disjunction->size += 1;
    return;
}
