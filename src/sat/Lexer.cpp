#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"

void Lexer::run() {
    size_t idx = 0;
    while (idx < program.length()) {
        char c = program[idx];
        if (isspace(c)) {
            idx++;
            continue;
        }
        switch (c) {
            case '(':
                addToken(TokenType::LPAREN);
                break;
            case ')':
                addToken(TokenType::RPAREN);
                break;
            case '!':
                addToken(TokenType::NOT);
                break;
            case '&':
                addToken(TokenType::AND);
                break;
            case '|':
                addToken(TokenType::OR);
                break;
            default:
                assert(isalpha(c) && "unexpected character while scanning");
                {
                    std::string str = "";
                    while (program[idx] != '\0' && isalpha(program[idx])) {
                        str += program[idx];
                        idx++;
                    }
                    addToken(TokenType::STRING, new std::string(str));
                }
                break;
        }
        idx++;
    }
}

void Lexer::addToken(TokenType type, std::string* value) {
    tokens.push_back(new Token(type, value));
}

void Token::print(std::ostream& os) const {
    printTokenType(type, os);
    if (type == TokenType::STRING) {
        assert(value != nullptr && "expected value in token");
        os << "[" << *value << "]";
    }
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
        case TokenType::STRING:
            os << "VAR";
            break;
        default:
            assert(false && "unexpected token type");
    }
}
