#ifndef SEALVM_PARSER_HEXSPARSER_HPP
#define SEALVM_PARSER_HEXSPARSER_HPP

#include <regex>

#include "parser/baseParser.hpp"
#include "parser/state.hpp"

namespace Parser {

// HexParser is used to check a given string only contains hex-allowed values
class HexParser : public BaseParser {
    public:
    HexParser();
    ~HexParser() = default;

    State* Run(State* state);

    private:
    std::regex regex;
};

} // namespace Parser

#endif // SEALVM_PARSER_HEXSPARSER_HPP