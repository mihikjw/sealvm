#ifndef SEALVM_PARSER_COREPARSER_HPP
#define SEALVM_PARSER_COREPARSER_HPP

#include <string>
#include <stdexcept>
#include <vector>
#include <list>
#include <memory>

#include "stringParser.hpp"
#include "state.hpp"

namespace Parser {

class CoreParser {
    public:
    CoreParser() = default;
    ~CoreParser() = default;

    State* Run(StringParser* parser, const std::string &in);

    State* SequenceOf(std::vector<std::unique_ptr<StringParser>>* parsers, const std::string &in);
};

}

#endif  // SEALVM_PARSER_COREPARSER_HPP