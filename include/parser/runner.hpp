#ifndef SEALVM_PARSER_RUNNER_HPP
#define SEALVM_PARSER_RUNNER_HPP

#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "baseParser.hpp"
#include "state.hpp"

namespace Parser {

class Runner {
    public:
    Runner() = default;
    ~Runner() = default;

    // Run executes a single parser on a single input
    State* Run(BaseParser* parser, const std::string& in);

    // SequenceOf executes a sequence of parsers against a given input
    State* SequenceOf(std::vector<std::unique_ptr<BaseParser>>* parsers, const std::string& in);
};

} // namespace Parser

#endif // SEALVM_PARSER_RUNNER_HPP