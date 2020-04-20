#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Token.h"
#include "Util.h"

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
    std::vector<Token*> getTokens() const {
        return toPtrVector(tokens);
    }

    /**
     * Retrieves the error log generated during lexing.
     * @return a vector of errors
     */
    const std::vector<std::string>& getErrors() const {
        return errors;
    }

private:
    std::string program;
    size_t idx{0};
    size_t line{0};
    size_t currLineStart{0};
    size_t currTokenStart{0};
    std::vector<std::unique_ptr<Token>> tokens{};
    std::vector<std::string> errors{};

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

    /**
     * Logs an error found during lexing.
     * @param line line the error was found
     * @param col column the error was found
     * @param message message to print
     */
    void logError(size_t line, size_t col, std::string message);
};
