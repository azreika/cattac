#include <cassert>
#include <memory>
#include <vector>

#include "Parser.h"
#include "Token.h"
#include "Util.h"

void Parser::run() {
    program = parseExpression();
    expect(TokenType::END);
}

std::unique_ptr<AstNode> Parser::parseExpression() {
    auto expression = parseConjunction();
    while (match(TokenType::OR)) {
        expression =
            std::make_unique<AstOr>(std::move(expression), parseExpression());
    }
    return expression;
}

std::unique_ptr<AstNode> Parser::parseConjunction() {
    auto impl = parseImplication();
    while (match(TokenType::AND)) {
        impl = std::make_unique<AstAnd>(std::move(impl), parseConjunction());
    }
    return impl;
}

std::unique_ptr<AstNode> Parser::parseImplication() {
    auto term = parseTerm();
    while (match(TokenType::DASH)) {
        expect(TokenType::GT);
        term =
            std::make_unique<AstImplies>(std::move(term), parseImplication());
    }
    return term;
}

std::unique_ptr<AstNode> Parser::parseTerm() {
    Token* curToken = advance();
    switch (curToken->getType()) {
        case TokenType::NOT: return std::make_unique<AstNot>(parseTerm());
        case TokenType::LPAREN: {
            auto expression = parseExpression();
            expect(TokenType::RPAREN);
            return expression;
        }
        case TokenType::VARIABLE:
            return std::make_unique<AstVariable>(curToken->getValue());
        default: {
            std::stringstream error;
            error << "Unexpected token ";
            printTokenType(curToken->getType(), error);
            logError(curToken, error.str());
            if (curToken->getType() == TokenType::END) {
                return std::make_unique<AstVariable>("@ERROR_VAR");
            } else {
                return parseTerm();
            }
        }
    }
}

void Parser::logError(const Token* token, std::string message) {
    size_t line = token->getLine();
    size_t col = token->getCol();

    std::stringstream error;
    error << "Error: " << message << " (on line " << line + 1 << ", column "
          << col + 1 << ")" << std::endl;
    errors.push_back(error.str());
}
