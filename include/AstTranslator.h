#pragma once

#include <map>
#include <memory>
#include <string>

#include "AstNode.h"
#include "SatNode.h"

/**
 * Translation unit that converts an AST formula into a more restricted SAT
 * formula.
 */
class AstTranslator {
public:
    AstTranslator(const AstNode* formula) : formula(formula) { run(); }

    /**
     * Return the SAT formula represented by the input AST.
     */
    SatConjunction* getSatFormula() const { return result.get(); }

private:
    /**
     * Types of internal assignments possible.
     */
    enum class AssignmentType {
        AND,
        NOT,
        OR,
        IMPLIES,
    };

    /**
     * Represents an internal assignment.
     */
    struct Assignment {
        AssignmentType type;
        std::string name;
        std::string op1;
        std::string op2;
    };

    const AstNode* formula;
    std::map<std::string, AstNode*> subformulaNames{};
    size_t numVars{0};
    std::vector<Assignment> assignments{};
    std::unique_ptr<SatConjunction> result{std::make_unique<SatConjunction>()};

    /**
     * Run the translator.
     */
    void run();

    /**
     * Add an assignment to the internal correspondence list.
     * @param type operand type of assignment to construct
     * @param name name of the new variable created
     * @param left operand of the assignment
     * @param right operand of the assignment (optional)
     */
    void addAssignment(AssignmentType type, std::string name,
                       std::string operand1, std::string operand2 = "") {
        assignments.push_back({type, name, operand1, operand2});
    }

    /**
     * Assign a name to every subformula in the given node.
     * @param node node to assign a name to
     * @return name assigned to the subformula
     */
    std::string nameSubformulas(const AstNode* node);

    /**
     * Construct a new unique name.
     * @return a name that has not previously been generated
     */
    std::string nextName();
};
