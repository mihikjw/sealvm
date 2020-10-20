#ifndef SEALVM_PARSER_STATE_HPP
#define SEALVM_PARSER_STATE_HPP

#include <list>
#include <memory>
#include <string>

#include "parser/baseParser.hpp"

namespace Parser {

// State represents the state of the parser
class State {

    public:
    // State default constructor
    State(const std::string& input = "", const std::string& result = "", std::shared_ptr<std::list<std::shared_ptr<State>>> results = nullptr,
          unsigned short index = 0, const std::string& error = "", bool isError = false);

    // State copy constructor
    State(State* in);

    // Transform applies the given transformation function to the State and returns it if no error exists on the state
    State* Transform(State*(transformer)(State*));

    // ErrorTransform applies the given transformation function to the State if an error exists on the state
    State* ErrorTransform(State*(transformer)(State*));

    // Input contains the input for the function
    std::string Input;

    // Result contains the output for the single function
    std::string Result;

    // Results contains the output for multiple functions chained together (i.e. CoreParser::SequenceOf result)
    std::shared_ptr<std::list<std::shared_ptr<State>>> Results;

    // Index contains the current index in the input of the parser function
    unsigned short Index;

    // Error contains any error message generated from the last executed function
    std::string Error;

    // IsError is a flag for the error message
    bool IsError;
};

} // namespace Parser

#endif // SEALVM_PARSER_STATE_HPP