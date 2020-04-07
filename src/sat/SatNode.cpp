#include "SatNode.h"

void SatConjunction::print(std::ostream& os) const {
    os << "(";
    for (size_t i = 0; i < disjunctions.size(); i++) {
        if (i != 0) {
            os << " & ";
        }
        os << *disjunctions[i];
    }
    os << ")";
}

void SatDisjunction::print(std::ostream& os) const {
    os << "(";
    for (size_t i = 0; i < atoms.size(); i++) {
        if (i != 0) {
            os << " | ";
        }
        os << *atoms[i];
    }
    os << ")";
}

void SatAtom::print(std::ostream& os) const {
    if (negated) {
        os << "!";
    }
    os << id;
}
