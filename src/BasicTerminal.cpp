#include "BasicTerminal.hpp"

#include <iostream>

std::string* BasicTerminal::nextLine() {
    std::cout << "(BASIC) ~> ";
    std::string line;
    if(!std::getline(std::cin, line)) {
        return nullptr;
    }
    return new std::string(line);
}

void BasicTerminal::printLine(const std::string& s) {
    std::cout << s << std::endl;
}
