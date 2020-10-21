#include <iostream>
#include <memory>

#include "parser/parser.hpp"

/*
this is the code for the ASM parser
it's currently wip, I'm focusing on building an extensable parser combinator before really building an ASM parser for the vm,
    any code in here is basically just for testing at the moment.
*/

// attempt to parse a MOV instruction, e.g: MOV [$42 + (!loc - $1F)], r1

Parser::State* upperOrLowerStr(Parser::Runner* r, std::string locate, const std::string& src, Parser::State* state = nullptr) {
    std::transform(locate.begin(), locate.end(), locate.begin(), ::toupper);
    auto uppercaseParser = Parser::StringParser(locate);
    std::transform(locate.begin(), locate.end(), locate.begin(), ::tolower);
    auto lowercaseParser = Parser::StringParser(locate);
    auto parsers = std::vector<Parser::BaseParser*>{&uppercaseParser, &lowercaseParser};
    return r->Choice(&parsers, src, state);
}

Parser::State* getRegister(Parser::Runner* r, const std::string& src, Parser::State* state = nullptr) {
    std::vector<std::string> registers{"r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "acc", "pc", "sp", "ip"};

    for (auto const& reg : registers) {
        state = upperOrLowerStr(r, reg, src, state);

        if (!state->IsError) {
            break;
        }
    }

    if (!state->IsError) {
        return state;
    }

    state->Error = "unable to match a register";
    return state;
}

Parser::State* getHexLiteral(Parser::Runner* r, const std::string& src, Parser::State* state = nullptr) {
    auto hexDefParser = Parser::StringParser("$");
    state = r->Run(&hexDefParser, src, state);

    if (state->IsError) {
        return state;
    }

    auto hexParser = Parser::HexParser();
    return r->Run(&hexParser, src, state);
}

Parser::State* movLitToReg(Parser::Runner* r, const std::string& src) {
    auto whitespaceParserForce = Parser::WhitespaceParser();
    auto whitespaceParserOpt = Parser::WhitespaceParser(true);
    auto comma = Parser::StringParser(",");

    auto state = upperOrLowerStr(r, "mov", src);
    state = r->Run(&whitespaceParserForce, src, state);
    state = getHexLiteral(r, src, state);
    state = r->Run(&comma, src, state);
    state = r->Run(&whitespaceParserOpt, src, state);
    state = getRegister(r, src, state);
    return r->Run(&whitespaceParserOpt, src, state); // skip any trailing whitespace
}

int main() {
    std::string input = "MOV $42, r1 ";
    auto runner = Parser::Runner();
    auto state = movLitToReg(&runner, input);

    if (!state->IsError) {
        std::cout << "No Error\n";
    } else {
        std::cerr << "Error: " << state->Error << std::endl;
    }
}
