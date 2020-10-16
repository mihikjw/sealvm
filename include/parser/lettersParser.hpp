#ifndef SEALVM_PARSER_LETTERSPARSER_HPP
#define SEALVM_PARSER_LETTERSPARSER_HPP

#include <regex>

#include "parser/baseParser.hpp"
#include "parser/state.hpp"

namespace Parser {

// LettersParser is used to parse a string into an array of individual characters
class LettersParser : public BaseParser {
    public:
    LettersParser() = default;
    ~LettersParser() = default;

    State* Run(State* state);

    private:
    const char* regex = "^[A-Za-z]+";
};

} // namespace Parser

#endif // SEALVM_PARSER_LETTERSPARSER_HPP