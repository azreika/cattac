#include <iostream>
#include <vector>

#include "AstNode.h"

void AstAnd::print(std::ostream& os) const {
    os << "(" << *left << " & " << *right << ")";
}

void AstOr::print(std::ostream& os) const {
    os << "(" << *left << " | " << *right << ")";
}

void AstNot::print(std::ostream& os) const {
    os << "!" << *operand;
}

void AstVar::print(std::ostream& os) const {
    os << id;
}
