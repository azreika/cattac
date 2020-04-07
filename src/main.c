#include <iostream>
#include "ast.h"
#include "lexer.h"
#include "sat.h"

int main(int argc, char** argv) {
    printf((char*) "Welcome to CattaC.\n");

    printf((char*) "SAT test:\n");
    SatDisjunction* porq = new SatDisjunction();
    SatAtom* p1 = new SatAtom("p", false);
    SatAtom* q1 = new SatAtom("q", false); 
    porq->addAtom(p1);
    porq->addAtom(q1);

    SatDisjunction* notq = new SatDisjunction();
    SatAtom* q2 = new SatAtom("q", true);
    notq->addAtom(q2);

    SatConjunction* result = new SatConjunction();
    result->addDisjunction(porq);
    result->addDisjunction(notq);
    std::cout << *result << std::endl;

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
    std::vector<token_t*> tokens = scan((char*) "(al & !(bk | caa)) | d\n");
    for (size_t i = 0; i < tokens.size(); i++) {
        if (i != 0) printf((char*) " ");
        print_token((token_t*) tokens[i]);
    }
    printf((char*) "\n");
    return 0;
}
