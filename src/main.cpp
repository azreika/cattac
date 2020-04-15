#include <fstream>
#include <iostream>
#include <sstream>

#include "AstNode.h"
#include "AstTranslator.h"
#include "Lexer.h"
#include "Parser.h"
#include "SatNode.h"
#include "SatSolver.h"

void runProgram(std::string program) {
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
}

void runInterpeter() {
    std::string program;
    std::cout << "> ";
    while (std::getline(std::cin, program)) {
        runProgram(program);
        std::cout << std::endl;
        std::cout << "> ";
    }
    if (std::cin.bad()) {
        std::cerr << "I/O error" << std::endl;
    }
}

void runFile(std::string filename) {
    std::ifstream inFile;
    inFile.open(filename);
    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string program = strStream.str();
    runProgram(program);
}

int main(int argc, char** argv) {
    if (argc == 1) {
        runInterpeter();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        std::cout << "Usage: " << argv[0] << " <OPTIONAL FILENAME>" << std::endl;
    }

    return 0;
}
