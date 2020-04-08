#pragma once

#include <cassert>
#include <vector>

#include "AstNode.h"
#include "Token.h"

class Parser {
public:
    Parser(const std::vector<Token*> tokens) : tokens(tokens) {
        run();
    }

    AstNode* getProgram() const {
        return program;
    }

private:
    const std::vector<Token*> tokens;
    size_t pos{0};
    AstNode* program;

    /**
     * Run the parser to produce the root program node.
     */
    void run();

    /**
     * Check the current token in the stream.
     * @return the token pointed to currently
     */
    Token* peek() const {
        assert(pos < tokens.size() && "pos out of range");
        return tokens[pos];
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
     * Advance the position pointer by one token.
     * @return the token the pointer was at
     */
    Token* advance() {
        assert(pos < tokens.size() && "pos out of range");
        return tokens[pos++];
    }

    /**
     * Parse an expression.
     * @return the expression read
     */
    AstNode* parseExpression();

    /**
     * Parse a conjunction.
     * @return the conjunction read
     */
    AstNode* parseConjunction();

    /**
     * Parse a term.
     * @return the term read
     */
    AstNode* parseTerm();
};
