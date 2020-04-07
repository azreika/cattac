#include <iostream>
#include "ast.h"
#include "lexer.h"
#include "SatNode.h"

int main(int argc, char** argv) {
    std::cout << "Welcome to CattaC." << std::endl;

    std::cout << "SAT test:" << std::endl;
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

    std::cout << std::endl;
    std::cout << "AST test [ (a & !(b v c)) v d ]:" << std::endl;

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
    std::cout << std::endl;

    destroy_ast_node(level0);

    std::cout << std::endl;
    std::cout << "Lexer test [ (al & !(bk | caa)) | d ]:" << std::endl;
    Lexer lexer = Lexer("(al & !(bk | caa)) | d\n");
    const auto& tokens = lexer.getTokens();
    for (size_t i = 0; i < tokens.size(); i++) {
        if (i != 0) std::cout << " ";
        print_token((token_t*) tokens[i]);
    }
    std::cout << std::endl;
    return 0;
}
