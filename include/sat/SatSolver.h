#pragma once

#include <map>

#include "SatNode.h"

class SatSolver {
public:
    SatSolver(const SatConjunction* formula) {
        satisfiable = solve(formula);
    }

    /**
     * Get the assignment needed for satisfiability.
     * Assumes the formula was satisfiable.
     * @return the assignment map
     */
    const std::map<std::string, bool>& getAssignments() const {
        assert(isSat() && "invalid analysis of unsat formula");
        return assignments;
    }

    /**
     * Check satisfiability of the input formula.
     * @return true iff the formula is satisfiable
     */
    bool isSat() const {
        return satisfiable;
    }

private:
    std::map<std::string, bool> assignments{};
    bool satisfiable;

    /**
     * Simplify a given formula under the current assignment.
     * @param formula formula to simplify
     * @return formula in CNF after simplification
     */
    std::unique_ptr<SatConjunction> simplify(const SatConjunction* formula) const;

    /**
     * Solve the given formula, updating the assignment map as needed.
     * @param formula formula to check satisfiability of
     * @return true iff the formula is sat under the current assignment
     */
    bool solve(const SatConjunction* formula);
};
