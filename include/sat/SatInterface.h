#pragma once

#include <string>

class SatInterface;
class CLIOptions;

class SatInterface {
public:
    SatInterface() = default;

    void setOptions(int argc, char** argv);

    void execute();

private:
    CLIOptions* opts;

    void executeREPL();

    void executeFile(std::string filename);

    void executeProgram(std::string program);
};

class CLIOptions {
public:
    CLIOptions(int argc, char** argv) {
        parseArguments(argc, argv);
    }

    std::string getHelpMessage() const;

    std::string execName{""};
    std::string filename{""};
    bool debug{false};
    bool help{false};
private:

    void parseArguments(int argc, char** argv);
};
