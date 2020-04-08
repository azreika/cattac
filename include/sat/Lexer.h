#pragma once

#include <string>
#include <vector>

#include "Token.h"

class Lexer;

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
    size_t idx{0};
    size_t line{0};
    size_t currLineStart{0};
    size_t currTokenStart{0};
    std::vector<Token*> tokens{};

    /**
     * Produce the token stream represented by the source program.
     */
    void run();

    /**
     * Checks whether the end of the program has been hit.
     * @return true iff there may be more tokens to scan
     */
    bool hasNext() const;

    /**
     * Scans the next token in the sequence.
     * @return the next token in the sequence
     */
    void scanNextToken();

    /**
     * Scans the identifier at the current point in the sequence.
     * @return the string representation of the identifier
     */
    std::string scanIdentifier();

    /**
     * Add a token to the internal token stream.
     * @param type type of token to add
     */
    void addToken(TokenType type);

    /**
     * Add a token with a value to the internal token stream.
     * @param type type of token to add
     * @param value (optional) value tied to the token
     */
    void addToken(TokenType type, std::string value);

    /**
     * Advance the pointer by one character.
     * @return the character that was being pointed to
     */
    char advance();

    /**
     * Peek at the current position in the program.
     * @return the current character being pointed to
     */
    char peek() const;
};
