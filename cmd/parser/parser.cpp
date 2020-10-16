#include <iostream>
#include <memory>

#include "parser/parser.hpp"

int main() {
    auto coreParser = Parser::CoreParser();

    auto parsers = std::make_unique<std::vector<std::unique_ptr<Parser::StringParser>>>();
    parsers->push_back(std::make_unique<Parser::StringParser>("hello there!"));
    parsers->push_back(std::make_unique<Parser::StringParser>("goodbye there!"));

    auto outState = std::make_unique<Parser::State>(coreParser.SequenceOf(parsers.get(), "hello there!goodbye there!"));

    if (!outState->IsError) {
        auto results = *outState->Results;
        for (const auto &r: results) {
            std::cout << r->Result << std::endl;
        }
    } else {
        std::cerr << outState->Error << std::endl;
    }
}

