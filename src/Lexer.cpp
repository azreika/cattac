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
        case '-': addToken(TokenType::DASH); break;
        case '>': addToken(TokenType::GT); break;

        default: {
            if (isalpha(c)) {
                addToken(TokenType::VARIABLE, scanIdentifier());
            } else {
                // Error!
                std::stringstream error;
                error << "Unexpected character '" << c << "'";
                logError(line, currTokenStart, error.str());
                addToken(TokenType::ERROR);

                // Skip until the next whitespace character
                while (hasNext() && !isspace(peek())) {
                    advance();
                }
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
    tokens.push_back(
        std::make_unique<Token>(type, currTokenStart - currLineStart, line));
}

void Lexer::addToken(TokenType type, std::string value) {
    tokens.push_back(std::make_unique<Token>(
        type, value, currTokenStart - currLineStart, line));
}

char Lexer::peek() const {
    assert(hasNext() && "unexpected idx position");
    return program[idx];
}

char Lexer::advance() {
    assert(hasNext() && "unexpected idx position");
    return program[idx++];
}

void Lexer::logError(size_t line, size_t col, std::string message) {
    std::stringstream error;
    error << "Error: " << message << " (on line " << line + 1 << ", column "
          << col + 1 << ")" << std::endl;
    errors.push_back(error.str());
}
