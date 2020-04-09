#pragma once

#include <map>

#include "AstNode.h"
#include "SatNode.h"

class AstTranslator {
public:
    AstTranslator(const AstNode* formula) : formula(formula) {
        run();
    }

    SatConjunction* getSatFormula() const {
        return result;
    }
private:
    const AstNode* formula;
    std::map<std::string, AstNode*> subformulaNames{};
    size_t numVars{0};
    SatConjunction* result{new SatConjunction()};

    void run();

    std::string nameSubformulas(const AstNode* node);

    std::string nextName();
};
