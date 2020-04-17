#include <fstream>
#include <iostream>
#include <regex>
#include <readline/readline.h>
#include <readline/history.h>
#include <sstream>
#include <string>

#include "AstNode.h"
#include "AstTranslator.h"
#include "Lexer.h"
#include "Parser.h"
#include "SatInterface.h"
#include "SatNode.h"
#include "SatSolver.h"

void SatInterface::setOptions(int argc, char** argv) {
    opts = std::make_unique<CLIOptions>(argc, argv);
}

void SatInterface::execute() {
    assert(opts != nullptr && "CLI options not set");

    if (opts->help) {
        std::cout << opts->getHelpMessage();
        return;
    }

    if (opts->filename != "") {
        executeFile(opts->filename);
    } else {
        executeREPL();
    }
}

void SatInterface::executeREPL() {
    while (char* line = readline("> ")) {
        if (!line) break;
        add_history(line);
        std::string program = std::string(line);
        free(line);
        executeProgram(program);
    }
    rl_clear_history();
}

void SatInterface::executeFile(std::string filename) {
    std::ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        std::cerr << "ERROR: File " << filename << " does not exist" << std::endl;
        return;
    }
    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string program = strStream.str();
    executeProgram(program);
}

template <typename T>
void printDebugInfo(std::string itemName, T* item) {
    std::cout << itemName << ":" << std::endl;
    std::cout << "---" << std::endl;
    std::cout << *item << std::endl;
    std::cout << "---" << std::endl;
    std::cout << std::endl;
}

void SatInterface::executeProgram(std::string program) {
    if (opts->debug) printDebugInfo("Program", &program);

    Lexer lexer(program);
    if (opts->debug) {
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
    }

    Parser parser(lexer.getTokens());
    if (opts->debug) printDebugInfo("Parsing", parser.getProgram());

    AstTranslator translator(parser.getProgram());
    if (opts->debug) printDebugInfo("Translation", translator.getSatFormula());

    SatSolver solver(translator.getSatFormula());
    if (solver.isSat()) {
        std::cout << "Satisfiable." << std::endl;
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

std::string CLIOptions::getHelpMessage() const {
    std::stringstream helpMessage;
    helpMessage << "Usage: " << execName << " [--debug] [--help] [FILE]" << std::endl;
    return helpMessage.str();
}

void CLIOptions::parseArguments(int argc, char** argv) {
    assert(argc >= 1 && "expected at least one argument");

    // Set executale name
    execName = argv[0];

    // Parse the rest of the options
    for (int i = 1; i < argc; i++) {
        std::string option(argv[i]);
        assert(option.length() > 0 && "expected non-empty string");
        if (option[0] != '-') {
            // String options
            //      filename
            if (filename != "") {
                help = true;
            }
            filename = option;
        } else if (option.length() == 1) {
            // '-' on its own
            help = true;
        } else if (option[1] == '-') {
            // Long-name options
            //      --debug
            //      --help
            std::string rest = option.substr(2, option.length()-2);
            rest == "debug" ? debug = true : help = true;
        } else {
            // Short-name options
            help = true;
        }
    }
}
