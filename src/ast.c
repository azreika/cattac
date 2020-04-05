#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ast_and_t* create_ast_and() {
    ast_and_t* and_op = malloc(sizeof(ast_and_t));
    and_op->operands = create_list();
    return and_op;
}

ast_or_t* create_ast_or() {
    ast_or_t* or_op = malloc(sizeof(ast_or_t));
    or_op->operands = create_list();
    return or_op;
}

ast_not_t* create_ast_not(void* operand) {
    ast_not_t* not_op = malloc(sizeof(ast_not_t));
    not_op->operand = operand;
    return not_op;
}

ast_var_t* create_ast_var(char* id) {
    ast_var_t* var = malloc(sizeof(ast_var_t));
    strncpy(var->id, id, MAX_ID_LEN);
    var->id[MAX_ID_LEN-1] = '\0';
    return var;
}

void destroy_ast_node(void* node) {
    ast_type_id type = ((struct ast_header_t*) node)->type;
    switch (type) {
        case ASTTYPE_AND:
            destroy_ast_and(node);
            break;
        case ASTTYPE_OR:
            destroy_ast_or(node);
            break;
        case ASTTYPE_NOT:
            destroy_ast_not(node);
            break;
        case ASTTYPE_VAR:
            destroy_ast_var(node);
            break;
        default:
            assert(false && "unexpected ast type");
    }
}

void destroy_ast_and(ast_and_t* and_op) {
    linked_list* operands = and_op->operands;
    for (uint64_t i = 0; i < operands->size; i++) {
        destroy_ast_node(operands->elements[i]);
    }
    free(and_op);
}

void destroy_ast_or(ast_or_t* or_op) {
    linked_list* operands = or_op->operands;
    for (uint64_t i = 0; i < operands->size; i++) {
        destroy_ast_node(operands->elements[i]);
    }
    free(or_op);
}

void destroy_ast_not(ast_not_t* not_op) {
    free(not_op->operand);
    free(not_op);
}

void destroy_ast_var(ast_var_t* var_op) {
    free(var_op);
}

void ast_and_append(ast_and_t* and_op, void* operand) {
    list_append(and_op->operands, operand);
}

void ast_or_append(ast_or_t* or_op, void* operand) {
    list_append(or_op->operands, operand);
}
