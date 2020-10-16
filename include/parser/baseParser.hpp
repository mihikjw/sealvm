#ifndef SEALVM_PARSER_BASEPARSER_HPP
#define SEALVM_PARSER_BASEPARSER_HPP

#include <string>

#include "parser/state.hpp"

namespace Parser {

class BaseParser {
    public:
    BaseParser() = default;
    ~BaseParser() = default;

    // Run executes the parser in the given input State, returns the modified State object
    virtual State* Run(State* state) = 0;

    protected:
    // setErrorState sets up the error fields on the given state, with the given error message
    State* setErrorState(State* state, const std::string& err) {
        state->Error = err;
        state->IsError = true;
        return state;
    }
};

} // namespace Parser

#endif // SEALVM_PARSER_BASEPARSER_HPP