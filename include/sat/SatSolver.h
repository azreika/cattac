#pragma once

#include <map>

#include "SatNode.h"

class SatSolver {
public:
    SatSolver(const SatConjunction* formula) {
        satisfiable = solve(formula);
    }

    const std::map<std::string, bool>& getAssignments() const {
        assert(satisfiable && "invalid analysis of unsat formula");
        return assignments;
    }

    bool isSat() const {
        return satisfiable;
    }

private:
    std::map<std::string, bool> assignments{};
    bool satisfiable;

    SatConjunction* simplify(const SatConjunction* formula) const {
        SatConjunction* newFormula = new SatConjunction();
        for (const auto* disj : formula->getDisjunctions()) {
            SatDisjunction* newDisj = new SatDisjunction();
            bool disjSatisfied = false;
            for (const auto* atom : disj->getAtoms()) {
                auto pos = assignments.find(atom->getName());
                if (pos != assignments.end()) {
                    bool isTrue = pos->second;
                    if (isTrue == !atom->isNegated()) {
                        // Disjunction satisfied!
                        disjSatisfied = true;
                        break;
                    } else {
                        // Atom failed, depend on the rest...
                    }
                } else {
                    // No change - keep the atom
                    newDisj->addAtom(new SatAtom(atom->getName(), atom->isNegated()));
                }
            }

            if (!disjSatisfied) {
                newFormula->addDisjunction(newDisj);
            }
        }
        return newFormula;
    }

    bool solve(const SatConjunction* formula) {
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
};
