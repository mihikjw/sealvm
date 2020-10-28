#include <iostream>
#include <memory>
#include <regex>

#include "parser/parser.hpp"
#include "sealasm/sealasm.hpp"

/*
this is the code for the ASM parser
it's currently wip, I'm focusing on building an extensable parser combinator before really building an ASM parser for the vm,
    any code in here is basically just for testing at the moment.
*/

int main() {
    std::string input = "MOV [$42 + (!loc - ($05 * $31))], r1";
    // std::string input = "MOV $42, r1";
    auto runner = Parser::Runner();

    auto processor = SealASM::Processor(&runner);
    processor.Process(input);
}
