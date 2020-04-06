#include <stdio.h>
#include "ast.h"
#include "lexer.h"
#include "sat.h"

int main(int argc, char** argv) {
    printf((char*) "Welcome to CattaC.\n");

    printf((char*) "SAT test:\n");
    sat_disj_t* porq = create_sat_disj();
    sat_atom_t* p1 = create_sat_atom((char*) "p", false);
    sat_atom_t* q1 = create_sat_atom((char*) "q", false);
    sat_add_atom(porq, p1);
    sat_add_atom(porq, q1);

    sat_disj_t* notq = create_sat_disj();
    sat_atom_t* q2 = create_sat_atom((char*) "q", true);
    sat_add_atom(notq, q2);

    sat_conj_t* result = create_sat_conj();
    sat_add_disjunction(result, porq);
    sat_add_disjunction(result, notq);

    print_sat_conj(result);
    printf((char*) "\n");
    destroy_sat_conj(result);

    printf((char*) "\n");
    printf((char*) "AST test [ (a & !(b v c)) v d ]:\n");

    // b v c
    ast_or_t* level0010 = create_ast_or();
    ast_var_t* level00100 = create_ast_var((char*) "b");
    ast_var_t* level00101 = create_ast_var((char*) "c");
    ast_or_append(level0010, level00100);
    ast_or_append(level0010, level00101);

    // !(b v c)
    ast_not_t* level001 = create_ast_not(level0010);

    // (a & !(b v c))
    ast_and_t* level00 = create_ast_and();
    ast_var_t* level000 = create_ast_var((char*) "a");
    ast_and_append(level00, level000);
    ast_and_append(level00, level001);

    // (a & !(b v c)) v d
    ast_or_t* level0 = create_ast_or();
    ast_var_t* level01 = create_ast_var((char*) "d");
    ast_or_append(level0, level00);
    ast_or_append(level0, level01);

    print_ast_node(level0);
    printf((char*) "\n");

    destroy_ast_node(level0);

    printf((char*) "\n");
    printf((char*) "Lexer test [ (al & !(bk | caa)) | d ]:\n");
    list* tokens = scan((char*) "(al & !(bk | caa)) | d\n");
    for (size_t i = 0; i < tokens->size; i++) {
        if (i != 0) printf((char*) " ");
        print_token((token_t*) tokens->elements[i]);
    }
    printf((char*) "\n");
    return 0;
}
