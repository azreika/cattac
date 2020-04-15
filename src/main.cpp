#include <fstream>
#include <iostream>
#include <sstream>

#include "AstNode.h"
#include "AstTranslator.h"
#include "Lexer.h"
#include "Parser.h"
#include "SatNode.h"
#include "SatSolver.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <FILENAME>" << std::endl;
        return 0;
    }

    std::ifstream inFile;
    inFile.open(argv[1]);
    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string program = strStream.str();

    std::cout << "Program:" << std::endl;
    std::cout << "---" << std::endl;
    std::cout << program << std::endl;
    std::cout << "---" << std::endl;
    std::cout << std::endl;

    Lexer lexer(program);
    std::cout << "Tokenisation:" << std::endl;
    std::cout << "---" << std::endl;
    const auto& tokens = lexer.getTokens();
    for (size_t i = 0; i < tokens.size(); i++) {
        if (i != 0) std::cout << " ";
        std::cout << *tokens[i];
    }
    std::cout << std::endl;
    std::cout << "---" << std::endl;
    std::cout << std::endl;

    Parser parser(lexer.getTokens());
    std::cout << "Parsing:" << std::endl;
    std::cout << "---" << std::endl;
    std::cout << *parser.getProgram() << std::endl;
    std::cout << "---" << std::endl;
    std::cout << std::endl;

    AstTranslator translator(parser.getProgram());
    std::cout << "Translation:" << std::endl;
    std::cout << "---" << std::endl;
    std::cout << *translator.getSatFormula() << std::endl;
    std::cout << "---" << std::endl;
    std::cout << std::endl;

    SatSolver solver(translator.getSatFormula());
    if (solver.isSat()) {
        std::cout << "Satisfiable!" << std::endl;
        std::cout << "Assignments: {";
        std::vector<std::string> truths;
        for (const auto& pair : solver.getAssignments()) {
            if (pair.first[0] == '@') continue;
            std::stringstream truth;
            if (!pair.second) truth << "!";
            truth << pair.first;
            truths.push_back(truth.str());
        }
        for (size_t i = 0; i < truths.size(); i++) {
            if (i != 0) std::cout << ", ";
            std::cout << truths[i];
        }
        std::cout << "}" << std::endl;
    } else {
        std::cout << "Unsatisfiable." << std::endl;
    }

    return 0;
}
