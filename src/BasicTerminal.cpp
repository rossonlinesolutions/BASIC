#include "BasicTerminal.hpp"

#include <iostream>

std::string* BasicTerminal::nextLine() {
    return readStdinConsole();
}

std::string* readStdinConsole() {
    std::cout << "(BASIC) ~> ";
    std::string line;
    if(!std::getline(std::cin, line)) {
        return nullptr;
    }
    return new std::string(line);
}

std::string* BasicTerminal::readStdin() {
    std::string line;
    if(!std::getline(std::cin, line)) {
        return nullptr;
    }
    return new std::string(line);
}

void BasicTerminal::printLine(const std::string& s) {
    std::cout << s << std::endl;
}
