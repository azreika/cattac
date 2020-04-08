#include <cassert>
#include <iostream>

#include "Token.h"

void Token::print(std::ostream& os) const {
    printTokenType(type, os);
    if (type == TokenType::VARIABLE) {
        os << "[" << value << "]";
    }
    os << "@(" << line << ":" << col << ")";
}

void printTokenType(const TokenType& tokenType, std::ostream& os) {
    switch (tokenType) {
        case TokenType::LPAREN:
            os << "LPAREN";
            break;
        case TokenType::RPAREN:
            os << "RPAREN";
            break;
        case TokenType::AND:
            os << "AND";
            break;
        case TokenType::OR:
            os << "OR";
            break;
        case TokenType::NOT:
            os << "NOT";
            break;
        case TokenType::VARIABLE:
            os << "VAR";
            break;
        default:
            assert(false && "unexpected token type");
    }
}
