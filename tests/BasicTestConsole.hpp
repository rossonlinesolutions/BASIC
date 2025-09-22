#pragma once

#include <BasicConsole.hpp>

class BasicTestConsole : public BasicConsole {
    public:
    std::string out;
    std::string src;
    std::string in;

    std::string* nextLine();
    void printLine(const std::string& s);
    std::string* readStdin();
};
