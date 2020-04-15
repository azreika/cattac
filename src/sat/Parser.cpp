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
    while (match(TokenType::OR)) {
        expression = new AstOr(expression, parseExpression());
    }
    return expression;
}

AstNode* Parser::parseConjunction() {
    AstNode* impl = parseImplication();
    while (match(TokenType::AND)) {
        impl = new AstAnd(impl, parseConjunction());
    }
    return impl;
}

AstNode* Parser::parseImplication() {
    AstNode* term = parseTerm();
    while (match(TokenType::DASH)) {
        assert(match(TokenType::GT) && "expected '>'");
        term = new AstImplies(term, parseImplication());
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
