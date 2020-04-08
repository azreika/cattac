#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"

void Lexer::run() {
    while (hasNext()) {
        currTokenStart = idx;
        scanNextToken();
    }
}

void Lexer::scanNextToken() {
    char c = advance();
    switch (c) {
        // Deal with whitespace
        case '\n': line += 1; col = 0;
        case ' ':
        case '\t': break;

        case '(': addToken(TokenType::LPAREN); break;
        case ')': addToken(TokenType::RPAREN); break;
        case '!': addToken(TokenType::NOT); break;
        case '&': addToken(TokenType::AND); break;
        case '|': addToken(TokenType::OR); break;

        default: {
            if (isalpha(c)) {
                addToken(TokenType::VARIABLE, scanIdentifier());
            } else {
                assert(false && "unexpected character");
            }
        }
    }
}

std::string Lexer::scanIdentifier() {
    while (hasNext() && isalpha(peek())) {
        advance();
    }
    return program.substr(currTokenStart, idx - currTokenStart);
}

bool Lexer::hasNext() const {
    assert(idx <= program.length() && "unexpected idx position");
    return idx < program.length();
}

void Lexer::addToken(TokenType type) {
    tokens.push_back(new Token(type));
}

void Lexer::addToken(TokenType type, std::string value) {
    tokens.push_back(new Token(type, std::move(value)));
}

char Lexer::peek() const {
    assert(hasNext() && "unexpected idx position");
    return program[idx];
}

char Lexer::advance() {
    assert(hasNext() && "unexpected idx position");
    col++;
    return program[idx++];
}

void Token::print(std::ostream& os) const {
    printTokenType(type, os);
    if (type == TokenType::VARIABLE) {
        os << "[" << value << "]";
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
        case TokenType::VARIABLE:
            os << "VAR";
            break;
        default:
            assert(false && "unexpected token type");
    }
}
