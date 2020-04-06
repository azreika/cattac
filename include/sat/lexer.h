#ifndef CATTAC_LEXER_H
#define CATTAC_LEXER_H

#include <vector>

#define MAX_STRING_LEN 256

// meta
typedef enum token_type_id {
    TOKENTYPE_LPAREN,
    TOKENTYPE_RPAREN,
    TOKENTYPE_STRING,
    TOKENTYPE_AND,
    TOKENTYPE_OR,
    TOKENTYPE_NOT,
} token_type_id;
typedef struct token_header_t token_header_t;

// token types
typedef struct token_t token_t;

struct token_header_t {
    token_type_id type;
};

// Lexer tokens
struct token_t {
    token_header_t header;
    void* value;
};

/**
 * Scan a program into a vector of tokens.
 * @param program program to parse
 * @return list of tokens
 */
std::vector<token_t*> scan(char* program);

/**
 * Create a token of the given type.
 * @param type type of the token to create
 * @return token with the given type
 */
token_t* create_token(token_type_id type);

/**
 * Print a token.
 * @param token token to print
 */
void print_token(token_t* token);

#endif // CATTAC_LEXER_H
