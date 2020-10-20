#ifndef SEALVM_PARSER_BETWEENPARSER_HPP
#define SEALVM_PARSER_BETWEENPARSER_HPP

#include <string>

#include "parser/baseParser.hpp"

namespace Parser {

// BetweenParser is used to extract text from between two characters
class BetweenParser : public BaseParser {
    public:
    BetweenParser(const std::string& leftFind, const std::string& rightFind) {
        left = leftFind;
        right = rightFind;
    }
    ~BetweenParser() = default;

    State* Run(State* state);

    private:
    std::string left;
    std::string right;
};

} // namespace Parser

#endif // SEALVM_PARSER_BETWEENPARSER_HPP