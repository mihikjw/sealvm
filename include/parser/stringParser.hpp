#ifndef SEALVM_PARSER_STRINGPARSER_HPP
#define SEALVM_PARSER_STRINGPARSER_HPP

#include <stdexcept>
#include <string>

#include "parser/baseParser.hpp"
#include "parser/state.hpp"

namespace Parser {

// StringParser is used to locate the given constructor string and set as the result on the state
class StringParser : public BaseParser {
    public:
    StringParser(const std::string& locate);
    ~StringParser() = default;

    State* Run(State* state);

    private:
    std::string locate;
};

} // namespace Parser

#endif // SEALVM_PARSER_STRINGPARSER_HPP