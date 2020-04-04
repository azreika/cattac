#include <stdio.h>
#include "sat.h"

int main(int argc, char** argv) {
    printf("Welcome to CattaC.\n");

    sat_disj_t* porq = create_sat_disj();
    sat_atom_t* p1 = create_sat_atom("p", false);
    sat_atom_t* q1 = create_sat_atom("q", false);
    sat_add_atom(porq, p1);
    sat_add_atom(porq, q1);

    sat_disj_t* notq = create_sat_disj();
    sat_atom_t* q2 = create_sat_atom("q", true);
    sat_add_atom(notq, q2);

    sat_conj_t* result = create_sat_conj();
    sat_add_disjunction(result, porq);
    sat_add_disjunction(result, notq);

    print_sat_conj(result);
    printf("\n");

    return 0;
}
