#pragma once

#include <iostream>
#include <string>

class Token;
enum class TokenType;

/**
 * Represents a type that a token type can belong to.
 */
enum class TokenType {
    LPAREN,
    RPAREN,
    VARIABLE,
    AND,
    OR,
    NOT,
    DASH,
    GT,
    END,
    ERROR,
};

/**
 * Represents a token in the SAT grammar.
 */
class Token {
public:
    Token(TokenType type, std::string value, size_t col, size_t line)
        : type(type), value(value), col(col), line(line) {}

    Token(TokenType type, size_t col, size_t line)
        : type(type), value(""), col(col), line(line) {}

    TokenType getType() const { return type; }

    std::string getValue() const { return value; }

    size_t getLine() const { return line; }

    size_t getCol() const { return col; }

    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
        token.print(os);
        return os;
    }

protected:
    void print(std::ostream& os) const;

private:
    TokenType type;
    std::string value;
    size_t col;
    size_t line;
};

/**
 * Print a given token type to an output stream.
 * @param tokenType token type to print
 * @param os output stream to redirect to
 */
void printTokenType(const TokenType& tokenType, std::ostream& os);
