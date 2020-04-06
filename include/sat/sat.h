#ifndef CATTAC_SAT_H
#define CATTAC_SAT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <vector>

#define MAX_ID_LEN 256

class SatNode;
class SatConjunction;
class SatDisjunction;
class SatAtom;

class SatNode {};

/**
 * Represents a conjunction of nested disjunctions.
 */
class SatConjunction : public SatNode {
public:
    std::vector<SatDisjunction*> disjunctions;

    /**
     * Add a disjunction to the conjunction.
     * @param disjunction disjunction to add
     */
    void addDisjunction(SatDisjunction* disjunction) {
        disjunctions.push_back(disjunction);
    }
};

/**
 * Represents a disjunction of nested atoms.
 */
class SatDisjunction : public SatNode {
public:
    std::vector<SatAtom*> atoms;

    /**
     * Add an atom to the disjunction.
     * @param atom atom to add
     */
    void addAtom(SatAtom* atom) {
        atoms.push_back(atom);
    }
};

/**
 * Represents a possibly negated atom.
 */
class SatAtom : public SatNode {
public:
    char id[MAX_ID_LEN];
    bool negated;
};

/**
 * Create a new SAT conjunction.
 * @return empty conjunction
 */
SatConjunction* create_sat_conj(void);

/**
 * Create a new SAT disjunction.
 * @return empty disjunction
 */
SatDisjunction* create_sat_disj(void);

/**
 * Create a new SAT atom.
 * @param id name of the atom
 * @param negated whether the atom is negated
 * @return corresponding atom
 */
SatAtom* create_sat_atom(char* id, bool negated);

/**
 * Destroy a SAT conjunction.
 * @param conjunction conjunction to destroy
 */
void destroy_sat_conj(SatConjunction* conjunction);

/**
 * Destroy a SAT disjunction.
 * @param disjunction disjunction to destroy
 */
void destroy_sat_disj(SatDisjunction* disjunction);

/**
 * Destroy a SAT atom.
 * @param atom atom to destroy
 */
void destroy_sat_atom(SatAtom* atom);

/**
 * Print a conjunction to stdout.
 * @param conjunction conjunction to print
 */
void print_sat_conj(SatConjunction* conjunction);

/**
 * Print a disjunction to stdout.
 * @param disjunction disjunction to print
 */
void print_sat_disj(SatDisjunction* disjunction);

/**
 * Print an atom to stdout.
 * @param atom atom to print
 */
void print_sat_atom(SatAtom* atom);

#endif // CATTAC_SAT_H
