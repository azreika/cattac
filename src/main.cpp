#include <iostream>
#include "AstNode.h"
#include "AstTranslator.h"
#include "Lexer.h"
#include "Parser.h"
#include "SatNode.h"
#include "SatSolver.h"

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
    AstVariable* level00100 = new AstVariable("b");
    AstVariable* level00101 = new AstVariable("c");
    AstOr* level0010 = new AstOr(level00100, level00101);

    // !(b v c)
    AstNot* level001 = new AstNot(level0010);

    // (a & !(b v c))
    AstVariable* level000 = new AstVariable("a");
    AstAnd* level00 = new AstAnd(level000, level001);

    // (a & !(b v c)) v d
    AstVariable* level01 = new AstVariable("d");
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

    AstTranslator* translator = new AstTranslator(parser->getProgram());
    std::cout << *translator->getSatFormula() << std::endl;

    std::string test = "!((p | q) & r) | (!s)";
    std::cout << "Test: " << test << std::endl;
    lexer = new Lexer(test);
    parser = new Parser(lexer->getTokens());
    translator = new AstTranslator(parser->getProgram());
    std::cout << *translator->getSatFormula() << std::endl;

    std::string sattest = "(p & (q | !p)) | (!p & !q)";
    std::cout << "Test: " << sattest << std::endl;
    lexer = new Lexer(sattest);
    parser = new Parser(lexer->getTokens());
    std::cout << "program: " << *parser->getProgram() << std::endl;
    translator = new AstTranslator(parser->getProgram());
    std::cout << *translator->getSatFormula() << std::endl;
    SatSolver* solver = new SatSolver(translator->getSatFormula());
    if (solver->isSat()) {
        std::cout << "<<SAT>>" << std::endl;
        for (const auto& pair : solver->getAssignments()) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    } else {
        std::cout << "<<UNSAT>>" << std::endl;
    }
    return 0;
}
