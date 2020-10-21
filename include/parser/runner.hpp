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
    State* Run(BaseParser* parser, const std::string& in, State* state = nullptr);

    // SequenceOf executes a sequence of parsers against a given input
    State* SequenceOf(std::vector<BaseParser*>* parsers, const std::string& in, State* state = nullptr);

    /* Choice attempts all given parsers in order, until one passes, then result is returned, errors do not stop the loop
    if no parsers succeed, then this is considered an error */
    State* Choice(std::vector<BaseParser*>* parsers, const std::string& in, State* state = nullptr);

    // Many will try to match the given parser as many times as it can. many1 arg tells to mark error if no matches, default is false
    State* Many(BaseParser* parser, const std::string& in, bool many1 = false, State* state = nullptr);
};

} // namespace Parser

#endif // SEALVM_PARSER_RUNNER_HPP