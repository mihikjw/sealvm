#include <iostream>
#include <memory>

#include "parser/parser.hpp"

int main() {
    auto runner = Parser::Runner();
    auto parser = Parser::LettersParser();
    auto outState = runner.Run(&parser, "hello3");

    if (!outState->IsError) {
        std::cout << outState->Result << std::endl;
    } else {
        std::cerr << outState->Error << std::endl;
    }
}

