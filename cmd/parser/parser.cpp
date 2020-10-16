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

    parsers.push_back(std::make_unique<Parser::StringParser>("blob"));
    parsers.push_back(std::make_unique<Parser::LettersParser>());
    parsers.push_back(std::make_unique<Parser::DigitsParser>());
    parsers.push_back(std::make_unique<Parser::LettersParser>());

    auto outState = runner.SequenceOf(&parsers, "blobhello1234goodbye");

    if (!outState->IsError) {
        auto results = *outState->Results;
        for (const auto &r : results) {
            std::cout << r->Result << std::endl;
        }
    } else {
        std::cerr << outState->Error << std::endl;
    }
}
