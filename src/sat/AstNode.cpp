#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AstNode.h"

ast_and_t* create_ast_and() {
    ast_and_t* and_op = (ast_and_t*) malloc(sizeof(ast_and_t));
    and_op->header.type = ASTTYPE_AND;
    and_op->operands = std::vector<void*>();
    return and_op;
}

ast_or_t* create_ast_or() {
    ast_or_t* or_op = (ast_or_t*) malloc(sizeof(ast_or_t));
    or_op->header.type = ASTTYPE_OR;
    or_op->operands = std::vector<void*>();
    return or_op;
}

ast_not_t* create_ast_not(void* operand) {
    ast_not_t* not_op = (ast_not_t*) malloc(sizeof(ast_not_t));
    not_op->header.type = ASTTYPE_NOT;
    not_op->operand = operand;
    return not_op;
}

ast_var_t* create_ast_var(char* id) {
    ast_var_t* var = (ast_var_t*) malloc(sizeof(ast_var_t));
    var->header.type = ASTTYPE_VAR;
    strncpy(var->id, id, MAX_ID_LEN);
    var->id[MAX_ID_LEN-1] = '\0';
    return var;
}

void destroy_ast_node(void* node) {
    ast_type_id type = ((struct ast_header_t*) node)->type;
    switch (type) {
        case ASTTYPE_AND:
            destroy_ast_and((ast_and_t*) node);
            break;
        case ASTTYPE_OR:
            destroy_ast_or((ast_or_t*) node);
            break;
        case ASTTYPE_NOT:
            destroy_ast_not((ast_not_t*) node);
            break;
        case ASTTYPE_VAR:
            destroy_ast_var((ast_var_t*) node);
            break;
        default:
            assert(false && "unexpected ast type");
    }
}

void destroy_ast_and(ast_and_t* and_op) {
    std::vector<void*> operands = and_op->operands;
    for (uint64_t i = 0; i < operands.size(); i++) {
        destroy_ast_node(operands[i]);
    }
    free(and_op);
}

void destroy_ast_or(ast_or_t* or_op) {
    std::vector<void*> operands = or_op->operands;
    for (uint64_t i = 0; i < operands.size(); i++) {
        destroy_ast_node(operands[i]);
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
    and_op->operands.push_back(operand);
}

void ast_or_append(ast_or_t* or_op, void* operand) {
    or_op->operands.push_back(operand);
}

void print_ast_and(ast_and_t* and_op) {
    printf("(");
    std::vector<void*> operands = and_op->operands;
    for (uint64_t i = 0; i < operands.size(); i++) {
        if (i != 0) {
            printf(" & ");
        }
        print_ast_node(operands[i]);
    }
    printf(")");
}

void print_ast_or(ast_or_t* or_op) {
    printf("(");
    std::vector<void*> operands = or_op->operands;
    for (uint64_t i = 0; i < operands.size(); i++) {
        if (i != 0) {
            printf(" | ");
        }
        print_ast_node(operands[i]);
    }
    printf(")");
}

void print_ast_not(ast_not_t* not_op) {
    printf("!(");
    print_ast_node(not_op->operand);
    printf(")");
}

void print_ast_var(ast_var_t* var_op) {
    printf("%s", var_op->id);
}

void print_ast_node(void* node) {
    ast_type_id type = ((struct ast_header_t*) node)->type;
    switch (type) {
        case ASTTYPE_AND:
            print_ast_and((ast_and_t*) node);
            break;
        case ASTTYPE_OR:
            print_ast_or((ast_or_t*) node);
            break;
        case ASTTYPE_NOT:
            print_ast_not((ast_not_t*) node);
            break;
        case ASTTYPE_VAR:
            print_ast_var((ast_var_t*) node);
            break;
        default:
            assert(false && "unexpected ast type");
    }
}
