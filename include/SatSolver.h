#pragma once

#include <map>

#include "SatNode.h"

class SatSolver {
public:
    SatSolver() = default;

    /**
     * Solve given the current internal state of the SAT solver.
     * @return true iff it is satisfiable
     */
    bool solve();

    /**
     * Add a new SAT formula to the internal formula.
     * @param newFormula formula to add
     */
    void addFormula(std::unique_ptr<SatNode> newFormula);

    /**
     * Get the assignment needed for satisfiability.
     * Assumes the formula was satisfiable.
     * @return the assignment map
     */
    const std::map<std::string, bool>& getAssignments() const {
        assert(solved && "sat solver has not been run yet!");
        assert(isSat() && "invalid analysis of unsat formula");
        return assignments;
    }

    /**
     * Check satisfiability of the input formula.
     * @return true iff the formula is satisfiable
     */
    bool isSat() const {
        assert(solved && "sat solver has not been run yet!");
        return satisfiable;
    }

private:
    std::map<std::string, bool> assignments{};
    bool satisfiable{false};
    bool solved{false};
    std::unique_ptr<SatConjunction> formula{std::make_unique<SatConjunction>()};

    /**
     * Simplify a given formula under the current assignment.
     * @param formula formula to simplify
     * @return formula in CNF after simplification
     */
    std::unique_ptr<SatConjunction>
    simplify(const SatConjunction* formula) const;

    /**
     * Solve the given formula, updating the assignment map as needed.
     * @param formula formula to check satisfiability of
     * @return true iff the formula is sat under the current assignment
     */
    bool solve(const SatConjunction* formula);

    /**
     * Invalidates the current assignment/solution cache.
     */
    void invalidate() {
        assignments.clear();
        solved = false;
        satisfiable = false;
    }
};
