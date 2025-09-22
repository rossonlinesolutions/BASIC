#pragma once

#include "BasicConsole.hpp"

#include <string>

class BasicTerminal : public BasicConsole {
    public:
    std::string* nextLine() override;
    std::string* readStdin() override;
    void printLine(const std::string& s) override;
};
