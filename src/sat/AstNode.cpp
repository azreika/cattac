#include <iostream>
#include <vector>

#include "AstNode.h"

void AstAnd::print(std::ostream& os) const {
    os << "(" << *left << " & " << *right << ")";
}

void AstOr::print(std::ostream& os) const {
    os << "(" << *left << " | " << *right << ")";
}

void AstImplies::print(std::ostream& os) const {
    os << "((" << *left << ") -> (" << *right << "))";
}

void AstNot::print(std::ostream& os) const {
    os << "!" << *operand;
}

void AstVariable::print(std::ostream& os) const {
    os << name;
}
