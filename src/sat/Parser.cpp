#include <cassert>
#include <vector>

#include "Parser.h"
#include "Token.h"

void Parser::run() {
    program = parseExpression();
    assert(match(TokenType::END) && "expected end of program");
}

AstNode* Parser::parseExpression() {
    AstNode* expression = parseConjunction();
    if (match(TokenType::OR)) {
        expression = new AstOr(expression, parseExpression());
    }
    return expression;
}

AstNode* Parser::parseConjunction() {
    AstNode* term = parseTerm();
    if (match(TokenType::AND)) {
        term = new AstAnd(term, parseExpression());
    }
    return term;
}

AstNode* Parser::parseTerm() {
    Token* curToken = advance();
    switch (curToken->getType()) {
        case TokenType::NOT:
            return new AstNot(parseTerm());
        case TokenType::LPAREN: {
            AstNode* expression = parseExpression();
            assert(match(TokenType::RPAREN) && "expected ')'");
            return expression;
        }
        case TokenType::VARIABLE:
            return new AstVariable(curToken->getValue());
        default:
            assert(false && "unexpected token");
    }
}
