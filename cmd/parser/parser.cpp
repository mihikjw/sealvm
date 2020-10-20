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

    // if (!outState2->IsError) {
    //     std::cout << outState2->Result << std::endl;
    // } else {
    //     std::cerr << outState2->Error << std::endl;
    // }
}
