#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"
#include "Token.h"

void Lexer::run() {
    while (hasNext()) {
        currTokenStart = idx;
        scanNextToken();
    }
    currTokenStart = idx;
    addToken(TokenType::END);
}

void Lexer::scanNextToken() {
    char c = advance();
    switch (c) {
        // Deal with whitespace
        case '\n': line += 1; currLineStart = idx;
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
    while (hasNext() && isalnum(peek())) {
        advance();
    }
    return program.substr(currTokenStart, idx - currTokenStart);
}

bool Lexer::hasNext() const {
    assert(idx <= program.length() && "unexpected idx position");
    return idx < program.length();
}

void Lexer::addToken(TokenType type) {
    tokens.push_back(new Token(type, currTokenStart - currLineStart, line));
}

void Lexer::addToken(TokenType type, std::string value) {
    tokens.push_back(new Token(type, value, currTokenStart - currLineStart, line));
}

char Lexer::peek() const {
    assert(hasNext() && "unexpected idx position");
    return program[idx];
}

char Lexer::advance() {
    assert(hasNext() && "unexpected idx position");
    return program[idx++];
}
