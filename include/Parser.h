#pragma once

#include <cassert>
#include <sstream>
#include <vector>

#include "AstNode.h"
#include "Token.h"

class Parser {
public:
    Parser(const std::vector<Token*> tokens) : tokens(tokens) {
        run();
    }

    const AstNode* getProgram() const {
        return program.get();
    }

    const std::vector<std::string> getErrors() const {
        return errors;
    }

private:
    const std::vector<Token*> tokens;
    size_t pos{0};
    std::unique_ptr<AstNode> program;
    std::vector<std::string> errors;

    /**
     * Run the parser to produce the root program node.
     */
    void run();

    /**
     * Check the current token in the stream.
     * @return the token pointed to currently
     */
    Token* peek() const {
        if (pos < tokens.size()) {
            return tokens[pos];
        }
        return tokens[tokens.size()-1];
    }

    /**
     * Check if a token match is found, and advance if true.
     * @param type token type to check for
     * @return true iff the current token type matches
     */
    bool match(TokenType type) {
        if (peek()->getType() == type) {
            advance();
            return true;
        }
        return false;
    }

    /**
     * Checks whether the expected token type is next in line.
     * Logs an error if this is not the case.
     * @param type token type to check for
     * @return true iff the correct token type is next
     */
    bool expect(TokenType type) {
        if (!match(type)) {
            std::stringstream error;
            error << "Expected ";
            printTokenType(type, error);
            error << " but got ";
            printTokenType(peek()->getType(), error);
            logError(peek(), error.str());
            return false;
        }
        return true;
    }

    /**
     * Advance the position pointer by one token.
     * @return the token the pointer was at
     */
    Token* advance() {
        if (pos < tokens.size()) {
            return tokens[pos++];
        }
        return tokens[tokens.size()-1];
    }

    /**
     * Parse an expression.
     * @return the expression read
     */
    std::unique_ptr<AstNode> parseExpression();

    /**
     * Parse a conjunction.
     * @return the conjunction read
     */
    std::unique_ptr<AstNode> parseConjunction();

    /**
     * Parse an implication.
     * @return the implication read
     */
    std::unique_ptr<AstNode> parseImplication();

    /**
     * Parse a term.
     * @return the term read
     */
    std::unique_ptr<AstNode> parseTerm();

    /**
     * Logs an error during parsing.
     * @param token token the error occurred on
     * @param message message to print
     */
    void logError(const Token* token, std::string message);
};
