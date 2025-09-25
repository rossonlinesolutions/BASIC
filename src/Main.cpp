#include "MainModule.cpp"

#include <iostream>

int runFile(char* filename) {
    BasicFileConsole console {filename};
    BasicInterpreter interpreter {console};
    interpreter.runInteractive();
    return 0;
}

int main(int argc, char** argv) {
    if(argc > 2) {
        return runFile(argv[1]);
    }

    std::cout << "Ross Online Solutions Tiny BASIC (main)" << std::endl;
    std::cout << "Version 1.0.0" << std::endl;

    // else run interactive
    BasicTerminal terminal;
    BasicInterpreter interpreter {terminal};

    interpreter.runInteractive();
    return 0;
}
