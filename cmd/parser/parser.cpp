#include <iostream>
#include <memory>

#include "parser/parser.hpp"

/*
this is the code for the ASM parser
it's currently wip, I'm focusing on building an extensable parser combinator before really building an ASM parser for the vm,
    any code in here is basically just for testing at the moment.
*/

int main() {
    auto runner = Parser::Runner();
    auto parser = Parser::LettersParser();
    auto parsers = std::vector<std::unique_ptr<Parser::BaseParser>>();
    parsers.push_back(std::make_unique<Parser::DigitsParser>());
    parsers.push_back(std::make_unique<Parser::LettersParser>());

    auto outState = runner.Choice(&parsers, "1234");

    if (!outState->IsError) {
        std::cout << outState->Result << std::endl;
    } else {
        std::cerr << outState->Error << std::endl;
    }
}
