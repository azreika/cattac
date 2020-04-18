#include <cassert>
#include <memory>

#include "SatSolver.h"

bool SatSolver::solve() {
    solved = true;
    satisfiable = solve(formula.get());
    return satisfiable;
}

void SatSolver::addFormula(std::unique_ptr<SatNode> newFormula) {
    invalidate();
    if (const auto* conjunction = dynamic_cast<SatConjunction*>(newFormula.get())) {
        for (const auto* disj : conjunction->getDisjunctions()) {
            formula->addDisjunction(std::unique_ptr<SatDisjunction>(disj->clone()));
        }
    } else if (const auto* disjunction = dynamic_cast<SatDisjunction*>(newFormula.get())) {
        formula->addDisjunction(std::unique_ptr<SatDisjunction>(disjunction->clone()));
    } else if (const auto* atom = dynamic_cast<SatAtom*>(newFormula.get())) {
        auto disj = std::make_unique<SatDisjunction>();
        disj->addAtom(std::unique_ptr<SatAtom>(atom->clone()));
        formula->addDisjunction(std::move(disj));
    } else {
        assert(false && "unexpected node type");
    }
}

std::unique_ptr<SatConjunction> SatSolver::simplify(const SatConjunction* formula) const {
    auto newFormula = std::make_unique<SatConjunction>();

    for (const auto* disj : formula->getDisjunctions()) {
        bool disjSatisfied = false;
        auto newDisj = std::make_unique<SatDisjunction>();

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
                newDisj->addAtom(std::unique_ptr<SatAtom>(atom->clone()));
            }
        }

        if (!disjSatisfied) {
            // Add in the atom if it hasn't been satisfied yet
            newFormula->addDisjunction(std::move(newDisj));
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
    if (solve(simplify(formula).get())) {
        return true;
    }

    // Failed - backtrack and try the opposite
    assignments[atom->getName()] = !atom->isNegated();
    if (solve(simplify(formula).get())) {
        return true;
    }

    // Unsatisfiable!
    assignments.erase(atom->getName());
    return false;
}
