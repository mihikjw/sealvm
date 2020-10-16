#ifndef SEALVM_PARSER_STRINGPARSER_HPP
#define SEALVM_PARSER_STRINGPARSER_HPP

#include <string> 
#include <stdexcept>
#include <stdint.h>

#include "parser/state.hpp"

namespace Parser {

class StringParser {
    public:
    StringParser(const std::string &locate);
    ~StringParser() = default;

    State* String(State* state);

    private:
    std::string locate;
};

}

#endif  // SEALVM_PARSER_STRINGPARSER_HPP