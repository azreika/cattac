#include <iostream>
#include <vector>

#include "AstNode.h"

void AstAnd::print(std::ostream& os) const {
    os << "(";
    for (size_t i = 0; i < operands.size(); i++) {
        if (i != 0) {
            os << " & ";
        }
        os << *operands[i];
    }
    os << ")";
}

void AstOr::print(std::ostream& os) const {
    os << "(";
    for (size_t i = 0; i < operands.size(); i++) {
        if (i != 0) {
            os << " | ";
        }
        os << *operands[i];
    }
    os << ")";
}

void AstNot::print(std::ostream& os) const {
    os << "!" << *operand;
}

void AstVar::print(std::ostream& os) const {
    os << id;
}
