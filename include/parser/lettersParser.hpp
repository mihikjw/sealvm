#ifndef SEALVM_PARSER_LETTERSPARSER_HPP
#define SEALVM_PARSER_LETTERSPARSER_HPP

#include <regex>

#include "parser/baseParser.hpp"
#include "parser/state.hpp"

namespace Parser {

// LettersParser is used to check a given string only contains letters
class LettersParser : public BaseParser {
    public:
    LettersParser();
    ~LettersParser() = default;

    State* Run(State* state);

    private:
    std::regex regex;
};

} // namespace Parser

#endif // SEALVM_PARSER_LETTERSPARSER_HPP