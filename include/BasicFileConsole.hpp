#pragma once

#include "BasicConsole.hpp"

#include <string>

extern std::string basic_read_file_reversed(const std::string& filename);

class BasicFileConsole : public BasicConsole {
    private:
    std::string content;

    public:
    BasicFileConsole(const std::string& filename) : content(basic_read_file_reversed(filename)) {
    }

    BasicFileConsole() : content("") {
    }

    void setContent(const std::string& content);
    std::string* nextLine() override;
    void printLine(const std::string& s) override;
};
