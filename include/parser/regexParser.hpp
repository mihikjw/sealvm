#ifndef SEALVM_PARSER_REGEXPARSER_HPP
#define SEALVM_PARSER_REGEXPARSER_HPP

#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "parser/baseParser.hpp"
#include "parser/state.hpp"

namespace Parser {

// RegexParser is used to check a given input for a regex match
class RegexParser : public BaseParser {
    public:
    RegexParser(const std::regex* regex);
    ~RegexParser() = default;

    State* Run(State* state);

    private:
    const std::regex* regex;
};

} // namespace Parser

#endif // SEALVM_PARSER_REGEXPARSER_HPP