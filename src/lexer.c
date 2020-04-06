#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

list* scan(char* program) {
    list* tokens = create_list();
    while (*program != '\0') {
        char c = *program;
        if (isspace(c)) {
            program++;
            continue;
        }
        switch (c) {
            case '(':
                list_append(tokens, create_token(TOKENTYPE_LPAREN));
                break;
            case ')':
                list_append(tokens, create_token(TOKENTYPE_RPAREN));
                break;
            case '!':
                list_append(tokens, create_token(TOKENTYPE_NOT));
                break;
            case '&':
                list_append(tokens, create_token(TOKENTYPE_AND));
                break;
            case '|':
                list_append(tokens, create_token(TOKENTYPE_OR));
                break;
            default:
                assert(isalpha(c) && "unexpected character while scanning");
                {
                    char* str = (char*) calloc(sizeof(char), MAX_STRING_LEN + 1);
                    size_t size = 0;
                    while (*program != '\0' && isalpha(*program)) {
                        assert(size < MAX_STRING_LEN && "string too long");
                        str[size++] = *(program++);
                    }
                    token_t* token = create_token(TOKENTYPE_STRING);
                    token->value = str;
                    list_append(tokens, token);
                }
                break;
        }
        program++;
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
            printf("STRING[%s]", (char*) token->value);
            break;
        default:
            assert(false && "unexpected token type");
    }
}
