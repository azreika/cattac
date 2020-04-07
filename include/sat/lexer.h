#ifndef CATTAC_LEXER_H
#define CATTAC_LEXER_H

#include <vector>

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

/**
 * Structure to carry out the lexing stage of language parsing.
 */
class Lexer {
public:
    Lexer(std::string program) : program(program) {
        run();
    }

    /**
     * Retrieve the token stream represented by the program.
     * @return a vector of tokens
     */
    const std::vector<token_t*>& getTokens() const {
        return tokens;
    }

private:
    std::string program;
    std::vector<token_t*> tokens{};

    /**
     * Add a token to the internal token stream.
     * @param type type of token to add
     * @param value (optional) value tied to the token
     */
    void addToken(token_type_id type, std::string* value = nullptr);

    /**
     * Produce the token stream represented by the source program.
     */
    void run();
};

// Lexer tokens
struct token_t {
    token_header_t header;
    std::string* value;
};

/**
 * Scan a program into a vector of tokens.
 * @param program program to parse
 * @return list of tokens
 */
std::vector<token_t*> scan(std::string program);

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
