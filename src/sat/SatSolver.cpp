#include <cassert>

#include "SatSolver.h"

SatConjunction* SatSolver::simplify(const SatConjunction* formula) const {
    SatConjunction* newFormula = new SatConjunction();

    for (const auto* disj : formula->getDisjunctions()) {
        bool disjSatisfied = false;
        SatDisjunction* newDisj = new SatDisjunction();

        for (const auto* atom : disj->getAtoms()) {
            auto pos = assignments.find(atom->getName());
            if (pos != assignments.end()) {
                // The assignment has an assigned value!
                bool isTrue = pos->second;
                if (isTrue == !atom->isNegated()) {
                    // Disjunction satisfied! Don't add it in.
                    disjSatisfied = true;
                    break;
                } else {
                    // Atom failed, but put the rest in
                }
            } else {
                // Atom not yet set - keep it in
                newDisj->addAtom(atom->clone());
            }
        }

        if (!disjSatisfied) {
            // Add in the atom if it hasn't been satisfied yet
            newFormula->addDisjunction(newDisj);
        }
    }
    return newFormula;
}

bool SatSolver::solve(const SatConjunction* formula) {
    // Check if trivially satisfiable
    if (formula->size() == 0) {
        return true;
    }

    // Check if trivially unsatisfiable
    SatAtom* atom = nullptr;
    for (const auto* disj : formula->getDisjunctions()) {
        if (disj->size() == 0) {
            return false;
        }
        if (atom == nullptr) {
            atom = disj->getAtoms()[0];
        }
    }

    // Not trivial - assign any variable
    assert(atom != nullptr && "unexpected nullptr atom");
    assignments[atom->getName()] = atom->isNegated();
    if (solve(simplify(formula))) {
        return true;
    }

    // Failed - backtrack and try the opposite
    assignments[atom->getName()] = !atom->isNegated();
    if (solve(simplify(formula))) {
        return true;
    }

    // Unsatisfiable!
    assignments.erase(atom->getName());
    return false;
}
