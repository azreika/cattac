#ifndef CATTAC_AST_H
#define CATTAC_AST_H

#include <vector>

#define MAX_ID_LEN 256

// meta
typedef enum ast_type_id {
    ASTTYPE_AND,
    ASTTYPE_OR,
    ASTTYPE_NOT,
    ASTTYPE_VAR
} ast_type_id;
typedef struct ast_header_t ast_header_t;

// ast node types
typedef struct ast_and_t ast_and_t;
typedef struct ast_or_t ast_or_t;
typedef struct ast_not_t ast_not_t;
typedef struct ast_var_t ast_var_t;

struct ast_header_t {
    ast_type_id type;
};

// AST "and"
struct ast_and_t {
    ast_header_t header;
    std::vector<void*> operands;
};

// AST "or"
struct ast_or_t {
    ast_header_t header;
    std::vector<void*> operands;
};

// AST "not"
struct ast_not_t {
    ast_header_t header;
    void* operand;
};

// AST variable
struct ast_var_t {
    ast_header_t header;
    char id[MAX_ID_LEN];
};

/**
 * Create a new AST "and".
 * @return empty and operation
 */
ast_and_t* create_ast_and(void);

/**
 * Create a new AST "or".
 * @return empty or operation
 */
ast_or_t* create_ast_or(void);

/**
 * Create a new AST "not".
 * @param operand operand to negate
 * @return not operation applied to the operand
 */
ast_not_t* create_ast_not(void* operand);

/**
 * Create a new AST variable.
 * @param id id of the variable
 * @return variable with the given id
 */
ast_var_t* create_ast_var(char* id);

/**
 * Destroy generic AST node.
 * @param node ast element to destroy
 */
void destroy_ast_node(void* node);

/**
 * Destroy an AST "and".
 * @param and_op and operation to destroy
 */
void destroy_ast_and(ast_and_t* and_op);

/**
 * Destroy an AST "or".
 * @param or_op or operation to destroy
 */
void destroy_ast_or(ast_or_t* or_op);

/**
 * Destroy an AST "not".
 * @param not_op not operation to destroy
 */
void destroy_ast_not(ast_not_t* not_op);

/**
 * Destroy an AST variable.
 * @param var variable to destroy
 */
void destroy_ast_var(ast_var_t* var_op);

/**
 * Add an operand to an "and".
 * @param and_op and operation to modify
 * @param operand operand to append
 */
void ast_and_append(ast_and_t* and_op, void* operand);

/**
 * Add an operand to an "or".
 * @param or_op or operation to modify
 * @param operand operand to append
 */
void ast_or_append(ast_or_t* or_op, void* operand);

/**
 * Print generic AST node.
 * @param node node to print
 */
void print_ast_node(void* node);

/**
 * Print an AST "and".
 * @param and_op and operation to print
 */
void print_ast_and(ast_and_t* and_op);

/**
 * Print an AST "or".
 * @param or_op and operation to print
 */
void print_ast_or(ast_or_t* or_op);

/**
 * Print an AST "not".
 * @param not_op not operation to print
 */
void print_ast_not(ast_not_t* not_op);

/**
 * Print an AST variable.
 * @param var_op variable to print
 */
void print_ast_var(ast_var_t* var_op);

#endif // CATTAC_AST_H
