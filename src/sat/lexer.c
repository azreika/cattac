#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"

std::vector<token_t*> scan(std::string program) {
    std::vector<token_t*> tokens;
    size_t idx = 0;
    while (idx < program.length()) {
        char c = program[idx];
        if (isspace(c)) {
            idx++;
            continue;
        }
        switch (c) {
            case '(':
                tokens.push_back(create_token(TOKENTYPE_LPAREN));
                break;
            case ')':
                tokens.push_back(create_token(TOKENTYPE_RPAREN));
                break;
            case '!':
                tokens.push_back(create_token(TOKENTYPE_NOT));
                break;
            case '&':
                tokens.push_back(create_token(TOKENTYPE_AND));
                break;
            case '|':
                tokens.push_back(create_token(TOKENTYPE_OR));
                break;
            default:
                assert(isalpha(c) && "unexpected character while scanning");
                {
                    std::string str = "";
                    while (program[idx] != '\0' && isalpha(program[idx])) {
                        str += program[idx];
                        idx++;
                    }
                    token_t* token = create_token(TOKENTYPE_STRING);
                    token->value = new std::string(str);
                    tokens.push_back(token);
                }
                break;
        }
        idx++;
    }
    return tokens;
}

token_t* create_token(token_type_id type) {
    token_t* token = (token_t*) malloc(sizeof(token_t));
    token->header.type = type;
    return token;
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
            std::cout << *token->value;
            break;
        default:
            assert(false && "unexpected token type");
    }
}
