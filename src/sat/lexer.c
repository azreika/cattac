#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"

void Lexer::run() {
    size_t idx = 0;
    while (idx < program.length()) {
        char c = program[idx];
        if (isspace(c)) {
            idx++;
            continue;
        }
        switch (c) {
            case '(':
                addToken(TOKENTYPE_LPAREN);
                break;
            case ')':
                addToken(TOKENTYPE_RPAREN);
                break;
            case '!':
                addToken(TOKENTYPE_NOT);
                break;
            case '&':
                addToken(TOKENTYPE_AND);
                break;
            case '|':
                addToken(TOKENTYPE_OR);
                break;
            default:
                assert(isalpha(c) && "unexpected character while scanning");
                {
                    std::string str = "";
                    while (program[idx] != '\0' && isalpha(program[idx])) {
                        str += program[idx];
                        idx++;
                    }
                    addToken(TOKENTYPE_STRING, new std::string(str));
                }
                break;
        }
        idx++;
    }
}

void Lexer::addToken(token_type_id type, std::string* value) {
    token_t* token = (token_t*) malloc(sizeof(token_t));
    token->header.type = type;
    token->value = value;
    tokens.push_back(token);
}

void print_token(token_t* token) {
    token_type_id type = ((struct token_header_t*) token)->type;
    switch (type) {
        case TOKENTYPE_LPAREN:
            printf("LPAREN");
            break;
        case TOKENTYPE_RPAREN:
            printf("RPAREN");
            break;
        case TOKENTYPE_AND:
            printf("AND");
            break;
        case TOKENTYPE_OR:
            printf("OR");
            break;
        case TOKENTYPE_NOT:
            printf("NOT");
            break;
        case TOKENTYPE_STRING:
            std::cout << "VAR[" << *token->value << "]";
            break;
        default:
            assert(false && "unexpected token type");
    }
}
