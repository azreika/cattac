#include <cassert>
#include <sstream>

#include "AstTranslator.h"

void AstTranslator::run() {
    nameSubformulas(formula);
    for (const auto& pair : subformulaNames) {
        const std::string& name = pair.first;
        const AstNode* sub = pair.second;
        if (const AstAnd* andOp = dynamic_cast<const AstAnd*>(sub)) {
            std::string A = static_cast<AstVar*>(andOp->getLeft())->getName();
            std::string B = static_cast<AstVar*>(andOp->getRight())->getName();

            SatDisjunction* first = new SatDisjunction();
            first->addAtom(new SatAtom(A, true));
            first->addAtom(new SatAtom(B, true));
            first->addAtom(new SatAtom(name, false));
            result->addDisjunction(first);

            SatDisjunction* second = new SatDisjunction();
            second->addAtom(new SatAtom(A, false));
            second->addAtom(new SatAtom(name, true));
            result->addDisjunction(second);

            SatDisjunction* third = new SatDisjunction();
            third->addAtom(new SatAtom(B, false));
            third->addAtom(new SatAtom(name, true));
            result->addDisjunction(third);
        } else if (const AstOr* orOp = dynamic_cast<const AstOr*>(sub)) {
            std::string A = static_cast<AstVar*>(orOp->getLeft())->getName();
            std::string B = static_cast<AstVar*>(orOp->getRight())->getName();

            SatDisjunction* first = new SatDisjunction();
            first->addAtom(new SatAtom(A, false));
            first->addAtom(new SatAtom(B, false));
            first->addAtom(new SatAtom(name, true));
            result->addDisjunction(first);

            SatDisjunction* second = new SatDisjunction();
            second->addAtom(new SatAtom(A, true));
            second->addAtom(new SatAtom(name, false));
            result->addDisjunction(second);

            SatDisjunction* third = new SatDisjunction();
            third->addAtom(new SatAtom(B, true));
            third->addAtom(new SatAtom(name, false));
            result->addDisjunction(third);
        } else if (const AstNot* notOp = dynamic_cast<const AstNot*>(sub)) {
            std::string A = static_cast<AstVar*>(notOp->getOperand())->getName();

            SatDisjunction* first = new SatDisjunction();
            first->addAtom(new SatAtom(A, true));
            first->addAtom(new SatAtom(name, true));
            result->addDisjunction(first);

            SatDisjunction* second = new SatDisjunction();
            second->addAtom(new SatAtom(A, false));
            second->addAtom(new SatAtom(name, false));
            result->addDisjunction(second);
        } else {
            assert(dynamic_cast<const AstVar*>(sub) && "unexpected ast node type");
        }
    }
}

std::string AstTranslator::nameSubformulas(const AstNode* node) {
    if (const AstAnd* andOp = dynamic_cast<const AstAnd*>(node)) {
        const std::string& left = nameSubformulas(andOp->getLeft());
        const std::string& right = nameSubformulas(andOp->getRight());
        std::string newName = nextName();
        subformulaNames[newName] = new AstAnd(new AstVar(left), new AstVar(right));
        return newName;
    } else if (const AstOr* orOp = dynamic_cast<const AstOr*>(node)) {
        const std::string& left = nameSubformulas(orOp->getLeft());
        const std::string& right = nameSubformulas(orOp->getRight());
        std::string newName = nextName();
        subformulaNames[newName] = new AstOr(new AstVar(left), new AstVar(right));
        return newName;
    } else if (const AstNot* notOp = dynamic_cast<const AstNot*>(node)) {
        const std::string& op = nameSubformulas(notOp->getOperand());
        std::string newName = nextName();
        subformulaNames[newName] = new AstNot(new AstVar(op));
        return newName;
    } else if (const AstVar* varOp = dynamic_cast<const AstVar*>(node)) {
        subformulaNames[varOp->getName()] = new AstVar(varOp->getName());
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
