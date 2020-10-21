#ifndef SEALVM_PARSER_WHITESPACEPARSER_HPP
#define SEALVM_PARSER_WHITESPACEPARSER_HPP

#include <string>

#include "parser/baseParser.hpp"
#include "parser/state.hpp"

namespace Parser {

// Whitespace parser is used to ensure the next character from the current index is whitespace
class WhitespaceParser : public BaseParser {
    public:
    WhitespaceParser(bool optional = false) { opt = optional; }
    ~WhitespaceParser() = default;

    State* Run(State* state);

    private:
    bool opt;
};

} // namespace Parser

#endif // SEALVM_PARSER_WHITESPACEPARSER_HPP