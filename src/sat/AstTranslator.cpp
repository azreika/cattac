#include <cassert>
#include <sstream>

#include "AstTranslator.h"

void AstTranslator::run() {
    // Construct the first disjunction - assigns "true" to the full formula
    std::string fullFormulaVariable = nameSubformulas(formula);
    SatDisjunction* formulaTruth = new SatDisjunction();
    formulaTruth->addAtom(new SatAtom(fullFormulaVariable, false));
    result->addDisjunction(formulaTruth);

    // Construct disjunctions to model all variable assignments created
    for (const auto& assignment : assignments) {
        switch (assignment.type) {
            case AssignmentType::AND: {
                SatDisjunction* first = new SatDisjunction();
                first->addAtom(new SatAtom(assignment.op1, true));
                first->addAtom(new SatAtom(assignment.op2, true));
                first->addAtom(new SatAtom(assignment.name, false));
                result->addDisjunction(first);

                SatDisjunction* second = new SatDisjunction();
                second->addAtom(new SatAtom(assignment.op1, false));
                second->addAtom(new SatAtom(assignment.name, true));
                result->addDisjunction(second);

                SatDisjunction* third = new SatDisjunction();
                third->addAtom(new SatAtom(assignment.op2, false));
                third->addAtom(new SatAtom(assignment.name, true));
                result->addDisjunction(third);
                break;
            }
            case AssignmentType::OR: {
                SatDisjunction* first = new SatDisjunction();
                first->addAtom(new SatAtom(assignment.op1, false));
                first->addAtom(new SatAtom(assignment.op2, false));
                first->addAtom(new SatAtom(assignment.name, true));
                result->addDisjunction(first);

                SatDisjunction* second = new SatDisjunction();
                second->addAtom(new SatAtom(assignment.op1, true));
                second->addAtom(new SatAtom(assignment.name, false));
                result->addDisjunction(second);

                SatDisjunction* third = new SatDisjunction();
                third->addAtom(new SatAtom(assignment.op2, true));
                third->addAtom(new SatAtom(assignment.name, false));
                result->addDisjunction(third);
                break;
            }
            case AssignmentType::IMPLIES: {
                SatDisjunction* first = new SatDisjunction();
                first->addAtom(new SatAtom(assignment.op1, true));
                first->addAtom(new SatAtom(assignment.op2, false));
                first->addAtom(new SatAtom(assignment.name, true));
                result->addDisjunction(first);

                SatDisjunction* second = new SatDisjunction();
                second->addAtom(new SatAtom(assignment.op1, false));
                second->addAtom(new SatAtom(assignment.name, false));
                result->addDisjunction(second);

                SatDisjunction* third = new SatDisjunction();
                third->addAtom(new SatAtom(assignment.op2, true));
                third->addAtom(new SatAtom(assignment.name, false));
                result->addDisjunction(third);
                break;
            }
            case AssignmentType::NOT: {
                assert(assignment.op2 == "" && "unexpected second operand");

                SatDisjunction* first = new SatDisjunction();
                first->addAtom(new SatAtom(assignment.op1, true));
                first->addAtom(new SatAtom(assignment.name, true));
                result->addDisjunction(first);

                SatDisjunction* second = new SatDisjunction();
                second->addAtom(new SatAtom(assignment.op1, false));
                second->addAtom(new SatAtom(assignment.name, false));
                result->addDisjunction(second);
                break;
            }
            default:
                assert(false && "unexpected assignment type");
        }
    }
}

std::string AstTranslator::nameSubformulas(const AstNode* node) {
    if (const AstAnd* andOp = dynamic_cast<const AstAnd*>(node)) {
        std::string left = nameSubformulas(andOp->getLeft());
        std::string right = nameSubformulas(andOp->getRight());
        std::string newName = nextName();
        addAssignment(AssignmentType::AND, newName, left, right);
        return newName;
    } else if (const AstOr* orOp = dynamic_cast<const AstOr*>(node)) {
        std::string left = nameSubformulas(orOp->getLeft());
        std::string right = nameSubformulas(orOp->getRight());
        std::string newName = nextName();
        addAssignment(AssignmentType::OR, newName, left, right);
        return newName;
    } else if (const AstImplies* impliesOp = dynamic_cast<const AstImplies*>(node)) {
        std::string left = nameSubformulas(impliesOp->getLeft());
        std::string right = nameSubformulas(impliesOp->getRight());
        std::string newName = nextName();
        addAssignment(AssignmentType::IMPLIES, newName, left, right);
        return newName;
    } else if (const AstNot* notOp = dynamic_cast<const AstNot*>(node)) {
        std::string op = nameSubformulas(notOp->getOperand());
        std::string newName = nextName();
        addAssignment(AssignmentType::NOT, newName, op);
        return newName;
    } else if (const AstVariable* varOp = dynamic_cast<const AstVariable*>(node)) {
        return varOp->getName();
    } else {
        assert(false && "unexpected ast node type");
    }
}

std::string AstTranslator::nextName() {
    std::stringstream name;
    name << "@var" << numVars++;
    return name.str();
}
