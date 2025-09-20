#pragma once

#include "BasicConsole.hpp"

#include <string>

class BasicTerminal : public BasicConsole {
    public:
    std::string* nextLine() override;
    void printLine(const std::string& s) override;
};
