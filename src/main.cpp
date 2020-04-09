#include <iostream>
#include "AstNode.h"
#include "Lexer.h"
#include "Parser.h"
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
    AstVar* level00100 = new AstVar((char*) "b");
    AstVar* level00101 = new AstVar((char*) "c");
    AstOr* level0010 = new AstOr(level00100, level00101);

    // !(b v c)
    AstNot* level001 = new AstNot(level0010);

    // (a & !(b v c))
    AstVar* level000 = new AstVar((char*) "a");
    AstAnd* level00 = new AstAnd(level000, level001);

    // (a & !(b v c)) v d
    AstVar* level01 = new AstVar((char*) "d");
    AstOr* level0 = new AstOr(level00, level01);

    std::cout << *level0 << std::endl;

    std::cout << std::endl;
    std::cout << "Lexer test [ (al & !(bk | caa)) | d ]:" << std::endl;
    Lexer* lexer = new Lexer("(al & !(bk | caa)) | d\n");
    const auto& tokens = lexer->getTokens();
    for (size_t i = 0; i < tokens.size(); i++) {
        if (i != 0) std::cout << " ";
        std::cout << *tokens[i];
    }
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Parsing test:" << std::endl;
    Parser* parser = new Parser(lexer->getTokens());
    std::cout << *parser->getProgram() << std::endl;
    return 0;
}
