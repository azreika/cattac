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
        AstOr* disjunction = new AstOr();
        disjunction->addOperand(expression);
        disjunction->addOperand(parseExpression());
        expression = disjunction;
    }
    return expression;
}

AstNode* Parser::parseConjunction() {
    AstNode* term = parseTerm();
    if (match(TokenType::AND)) {
        AstAnd* conjunction = new AstAnd();
        conjunction->addOperand(term);
        conjunction->addOperand(parseExpression());
        term = conjunction;
    }
    return term;
}

AstNode* Parser::parseTerm() {
    Token* curToken = advance();
    switch (curToken->getType()) {
        case TokenType::NOT:
            return new AstNot(parseExpression());
        case TokenType::LPAREN: {
            AstNode* expression = parseExpression();
            assert(match(TokenType::RPAREN) && "expected ')'");
            return expression;
        }
        case TokenType::VARIABLE:
            return new AstVar(curToken->getValue());
        default:
            assert(false && "unexpected token");
    }
}
