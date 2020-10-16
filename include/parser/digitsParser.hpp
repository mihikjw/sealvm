#ifndef SEALVM_PARSER_DIGITSPARSER_HPP
#define SEALVM_PARSER_DITIRSPARSER_HPP

#include <regex>
#include <string>

#include "parser/baseParser.hpp"
#include "parser/state.hpp"

namespace Parser {

// DigitsParser is used to check a given string only contains numberical digits
class DigitsParser : public BaseParser {
    public:
    DigitsParser();
    ~DigitsParser() = default;

    State* Run(State* state);

    private:
    std::regex regex;
};

} // namespace Parser

#endif // SEALVM_PARSER_DITIRSPARSER_HPP