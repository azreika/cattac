#pragma once

#include <string>
#include <vector>

class Lexer;
class Token;
enum class TokenType;

/**
 * Structure to carry out the lexing stage of SAT language parsing.
 */
class Lexer {
public:
    Lexer(std::string program) : program(program) {
        run();
    }

    /**
     * Retrieve the token stream represented by the program.
     * @return a vector of tokens
     */
    const std::vector<Token*>& getTokens() const {
        return tokens;
    }

private:
    std::string program;
    std::vector<Token*> tokens{};

    /**
     * Add a token to the internal token stream.
     * @param type type of token to add
     * @param value (optional) value tied to the token
     */
    void addToken(TokenType type, std::string* value = nullptr);

    /**
     * Produce the token stream represented by the source program.
     */
    void run();
};

/**
 * Represents a type that a token type can belong to.
 */
enum class TokenType {
    LPAREN,
    RPAREN,
    STRING,
    AND,
    OR,
    NOT,
};

/**
 * Represents a token in the SAT grammar.
 */
class Token {
public:
    Token(TokenType type, std::string* value) : type(type), value(value) {}
    Token(TokenType type) : type(type), value(nullptr) {}

    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
        token.print(os);
        return os;
    }

protected:
    void print(std::ostream& os) const;

private:
    TokenType type;
    std::string* value;
};

/**
 * Print a given token type to an output stream.
 * @param tokenType token type to print
 * @param os output stream to redirect to
 */
void printTokenType(const TokenType& tokenType, std::ostream& os);
