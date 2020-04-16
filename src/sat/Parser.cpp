#include <cassert>
#include <memory>
#include <vector>

#include "Parser.h"
#include "Token.h"
#include "Util.h"

void Parser::run() {
    program = std::move(parseExpression());
    assert(match(TokenType::END) && "expected end of program");
}

std::unique_ptr<AstNode> Parser::parseExpression() {
    auto expression = parseConjunction();
    while (match(TokenType::OR)) {
        expression = std::make_unique<AstOr>(std::move(expression),
                parseExpression());
    }
    return std::move(expression);
}

std::unique_ptr<AstNode> Parser::parseConjunction() {
    auto impl = parseImplication();
    while (match(TokenType::AND)) {
        impl = std::make_unique<AstAnd>(std::move(impl),
                parseConjunction());
    }
    return std::move(impl);
}

std::unique_ptr<AstNode> Parser::parseImplication() {
    auto term = parseTerm();
    while (match(TokenType::DASH)) {
        assert(match(TokenType::GT) && "expected '>'");
        term = std::make_unique<AstImplies>(std::move(term),
                parseImplication());
    }
    return std::move(term);
}

std::unique_ptr<AstNode> Parser::parseTerm() {
    Token* curToken = advance();
    switch (curToken->getType()) {
        case TokenType::NOT:
            return std::make_unique<AstNot>(parseTerm());
        case TokenType::LPAREN: {
            auto expression = parseExpression();
            assert(match(TokenType::RPAREN) && "expected ')'");
            return std::move(expression);
        }
        case TokenType::VARIABLE:
            return std::make_unique<AstVariable>(curToken->getValue());
        default:
            assert(false && "unexpected token");
    }
}
