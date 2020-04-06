#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "sat.h"

SatConjunction* create_sat_conj(void) {
    SatConjunction* ret = (SatConjunction*) malloc(sizeof(SatConjunction));
    ret->disjunctions = std::vector<SatDisjunction*>();
    return ret;
}

SatDisjunction* create_sat_disj(void) {
    SatDisjunction* ret = (SatDisjunction*) malloc(sizeof(SatDisjunction));
    ret->atoms = std::vector<SatAtom*>();
    return ret;
}

SatAtom* create_sat_atom(char* id, bool negated) {
    SatAtom* ret = (SatAtom*) malloc(sizeof(SatAtom));

    strncpy(ret->id, id, MAX_ID_LEN);
    ret->id[MAX_ID_LEN-1] = '\0';

    ret->negated = negated;

    return ret;
}

void destroy_sat_conj(SatConjunction* conjunction) {
    std::vector<SatDisjunction*> disjunctions = conjunction->disjunctions;
    for (uint64_t i = 0; i < disjunctions.size(); i++) {
        destroy_sat_disj((SatDisjunction*) disjunctions[i]);
    }
    free(conjunction);
}

void destroy_sat_disj(SatDisjunction* disjunction) {
    std::vector<SatAtom*> atoms = disjunction->atoms;
    for (uint64_t i = 0; i < atoms.size(); i++) {
        destroy_sat_atom((SatAtom*) atoms[i]);
    }
    free(disjunction);
}

void destroy_sat_atom(SatAtom* atom) {
    free(atom);
}

void print_sat_conj(SatConjunction* conjunction) {
    std::vector<SatDisjunction*> disjunctions = conjunction->disjunctions;
    printf("( ");
    for (size_t i = 0; i < disjunctions.size(); i++) {
        if (i != 0) {
            printf(" & ");
        }
        print_sat_disj((SatDisjunction*) disjunctions[i]);
    }
    printf(" )");
}

void print_sat_disj(SatDisjunction* disjunction) {
    std::vector<SatAtom*> atoms = disjunction->atoms;
    printf("( ");
    for (size_t i = 0; i < atoms.size(); i++) {
        if (i != 0) {
            printf(" | ");
        }
        print_sat_atom((SatAtom*) atoms[i]);
    }
    printf(" )");
}

void print_sat_atom(SatAtom* atom) {
    if (atom->negated) {
        printf("!");
    }
    printf("%s", atom->id);
}
