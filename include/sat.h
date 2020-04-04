#ifndef CATTAC_SAT_H
#define CATTAC_SAT_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_ID_LEN 256
#define INIT_CAP 32

typedef struct sat_conj_t sat_conj_t;
typedef struct sat_disj_t sat_disj_t;
typedef struct sat_atom_t sat_atom_t;

// SAT Conjunctions
struct sat_conj_t {
    sat_disj_t** disjunctions;
    uint64_t size;
    uint64_t cap;
};

// SAT Disjunctions
struct sat_disj_t {
    sat_atom_t** atoms;
    uint64_t size;
    uint64_t cap;
};

// SAT Atoms
struct sat_atom_t {
    char id[MAX_ID_LEN];
    bool negated;
};

/**
 * Create a new SAT conjunction.
 * @return empty conjunction
 */
sat_conj_t* create_sat_conj(void);

/**
 * Create a new SAT disjunction.
 * @return empty disjunction
 */
sat_disj_t* create_sat_disj(void);

/**
 * Create a new SAT atom.
 * @param id name of the atom
 * @param negated whether the atom is negated
 * @return corresponding atom
 */
sat_atom_t* create_sat_atom(char* id, bool negated);

/**
 * Destroy a SAT conjunction.
 * @param conjunction conjunction to destroy
 */
void destroy_sat_conj(sat_conj_t* conjunction);

/**
 * Destroy a SAT disjunction.
 * @param disjunction disjunction to destroy
 */
void destroy_sat_disj(sat_disj_t* disjunction);

/**
 * Destroy a SAT atom.
 * @param atom atom to destroy
 */
void destroy_sat_atom(sat_atom_t* atom);

/**
 * Add a disjunction to a conjunction.
 * @param conjunction conjunction to modify
 * @param disjunction disjunction to add
 */
void sat_add_disjunction(sat_conj_t* conjunction, sat_disj_t* disjunction);

/**
 * Add an atom to a disjunction.
 * @param disjunction disjunction to modify
 * @param atom atom to add
 */
void sat_add_atom(sat_disj_t* disjunction, sat_atom_t* atom);

#endif // CATTAC_SAT_H
