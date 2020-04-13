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

SatConjunction* SatConjunction::clone() const {
    SatConjunction* result = new SatConjunction();
    for (const auto* disj : disjunctions) {
        result->addDisjunction(disj->clone());
    }
    return result;
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

SatDisjunction* SatDisjunction::clone() const {
    SatDisjunction* result = new SatDisjunction();
    for (const auto* atom : atoms) {
        result->addAtom(atom->clone());
    }
    return result;
}

void SatAtom::print(std::ostream& os) const {
    if (negated) {
        os << "!";
    }
    os << name;
}

SatAtom* SatAtom::clone() const {
    return new SatAtom(name, negated);
}
